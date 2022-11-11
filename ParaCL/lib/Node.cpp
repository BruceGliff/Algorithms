#include "Node.hpp"

llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder(TheContext);
std::unique_ptr<llvm::Module> TheModule;
std::map<std::string, llvm::Value *> NamedValues;

Value *LogErrorV(const char *Str) {
//   llvm::LogError(Str);
    std::cout << Str << std::endl;
  return nullptr;
}


Node::~Node() {}
// NUMBER
RType Value::calc()
{
    return val;
}
llvm::Value *Value::codegen()  {
    return llvm::ConstantInt::get(TheContext, llvm::APInt(32, val));
}
void Value::dump() const
{
    std::cout << "Node Value: " << val << std::endl;
}
Value::~Value() {}

RType Decl::calc()
{
    return val;
}
llvm::Value *Decl::codegen() {
    return v;
}
void Decl::dump() const
{
    std::cout << "Node Decl: " << val << std::endl;
}
void Decl::SetValue(int Val)
{
   val = Val;
}
Decl::~Decl() {}

// SCOPE

RType Scope::calc()
{
    for (auto x : branches)
        x->calc();

    return 0;
}
llvm::Value *Scope::codegen() {
    // TODO BasicBlock?
    llvm::Value *TheLast = nullptr;
    for (auto &&x : branches)
        TheLast = x->codegen();
    return TheLast;
}
void Scope::dump() const
{
    std::cout << "Node Scope: " << std::endl;
    for (auto const x : branches)
        x->dump();
}
Scope * Scope::resetScope() const { return prev_scope; }
void Scope::addBranch(Node * branch)
{
    branches.push_back(branch);
}

Node * Scope::operator[](std::string const & var_name)
{
    Node * t = existsLater(var_name);
    if (t)
        return t;

    Node * dec = new Decl;
    memory[var_name] = dec;
    return dec;

        // if (memory.find(var_name) == memory.end())
        // {
        //     if (prev_scope)
        //         return prev_scope->operator[](var_name);
            
        //     Decl * dec = new Decl;
        //     memory[var_name] = dec;
        //     return dec;
        // }

        // return memory[var_name];
}
Node * Scope::existsLater(std::string const & var_name)
{
    Node * f = nullptr;
    if (memory.find(var_name) != memory.end())
        return memory[var_name];
    if (prev_scope && !f)
        f = prev_scope->existsLater(var_name);

    return f;
}

Scope::~Scope()
{
    for (auto x : branches)
        delete x;

    for (auto x : memory)
        delete x.second;
}

RType Op::calc()
{
    int val = 0;
    switch (op)
    {
    case Ops::Plus:
        if (left == nullptr)
            return 0 + right->calc();
        return left->calc() + right->calc();
        break;
    case Ops::Minus:
        if (left == nullptr)
            return 0 - right->calc();
        return left->calc() - right->calc();
        break;
    case Ops::Greater:
        return left->calc() > right->calc();
        break;
    case Ops::Less:
        return left->calc() < right->calc();
        break;
    case Ops::GreaterEq:
        return left->calc() >= right->calc();
        break;
    case Ops::LessEq:
        return left->calc() <= right->calc();
        break;
    case Ops::Assign:
        val = right->calc();
        static_cast<Decl * >(left)->SetValue(val);
        return val;
        break;
    case Ops::StdOut:
        std::cout << right->calc() << std::endl;
        break;
    case Ops::StdIn:
        std::cin >> val;
        return val;
        break;
    case Ops::Equal:
        return (left->calc() == right->calc());
        break;
    case Ops::NotEqual:
        return (left->calc() != right->calc());
        break;
    case Ops::Not:
        return !static_cast<bool>(right->calc());
        break;
    case Ops::And:
        return left->calc() && right->calc();
        break;
    case Ops::Or:
        return left->calc() || right->calc();
        break;
    case Ops::Div:
        val = right->calc();
        if (!val)
        {
            std::cout << "Division by zero!" << std::endl;
            exit(1);
        }
        return left->calc() / right->calc();
        break;
    case Ops::Mul:
        return left->calc() * right->calc();
        break;
    case Ops::Mod:
        return left->calc() % right->calc();
        break;
    default:
        return 999;
    }

    return 998;
}
llvm::Value *Op::codegen() {

    switch (op)
    {
    case Ops::Plus:
        if (left == nullptr)
            return right->codegen();
        return Builder.CreateAdd(left->codegen(), right->codegen(), "add");
        break;
    case Ops::Minus:
        if (left == nullptr)
            return Builder.CreateNeg(right->codegen(), "neg");
        return Builder.CreateSub(left->codegen(), right->codegen(), "sub");
        break;
    case Ops::Greater:
        return Builder.CreateICmpSGT(left->codegen(), right->codegen(), "sgt");
        break;
    case Ops::Less:
        return Builder.CreateICmpSLT(left->codegen(), right->codegen(), "slt");
        break;
    case Ops::GreaterEq:
        return Builder.CreateICmpSGE(left->codegen(), right->codegen(), "eq");
        break;
    case Ops::LessEq:
        return Builder.CreateICmpSLE(left->codegen(), right->codegen(), "sle");
        break;
    case Ops::Assign:
        static_cast<Decl * >(left)->SetValue(right->codegen());
        return left->codegen();
        break;
    // TODO
    case Ops::StdOut:
        std::cerr << "Not supported.\n";
        return nullptr;
        break;
    case Ops::StdIn:
        std::cerr << "Not supported.\n";
        return nullptr;
        break;
    case Ops::Equal:
        return Builder.CreateICmpEQ(left->codegen(), right->codegen(), "eq");
        break;
    case Ops::NotEqual:
        return Builder.CreateICmpNE(left->codegen(), right->codegen(), "ne");
        break;
    case Ops::Not:
        return Builder.CreateNot(right->codegen(), "not");
        break;
    case Ops::And:
        return Builder.CreateAnd(left->codegen(), right->codegen(), "and");
        break;
    case Ops::Or:
        return Builder.CreateOr(left->codegen(), right->codegen(), "or");
        break;
    case Ops::Div:
        return Builder.CreateSDiv(left->codegen(), right->codegen(), "div");
        break;
    case Ops::Mul:
        return Builder.CreateMul(left->codegen(), right->codegen(), "mul");
        break;
    case Ops::Mod:
        return Builder.CreateSRem(left->codegen(), right->codegen(), "rem");
        break;
    default:
        return nullptr;
    }

    return nullptr;
}
void Op::dump() const
{
    std::cout << "Node Op: ";
    int val = 0;
    switch (op)
    {
    case Ops::Plus:
        std::cout << "Plus" << std::endl;
        if (left == nullptr)
            right->dump();
        else 
        {
            left->dump();
            right->dump();
        }
        break;
    case Ops::Minus:
        std::cout << "Minus" << std::endl;
        if (left == nullptr)
            right->dump();
        else 
        {
            left->dump();
            right->dump();
        }
        break;
    case Ops::Greater:
        std::cout << "Greater" << std::endl;
        left->dump();
        right->dump();
        break;
    case Ops::Less:
        std::cout << "Less" << std::endl;
        left->dump();
        right->dump();
        break;
    case Ops::Assign:
        std::cout << "Assign" << std::endl;
        left->dump();
        right->dump();
        break;
    case Ops::StdOut:
        std::cout << "StdOut" << std::endl;
        right->dump();
        break;
    case Ops::StdIn:
        std::cout << "StdIn" << std::endl;
        break;
    case Ops::Equal:
        std::cout << "Equal" << std::endl;
        left->dump();
        right->dump();
        break;
    }
}
Op::~Op() 
{ 
    if (left && typeid(Decl) != typeid(*left))
        delete left;
    if (right && typeid(Decl) != typeid(*right))
        delete right;
}


RType While::calc()
{
    while(op->calc())
        scope->calc();

    return 0;
}
llvm::Value *While::codegen() {
    return nullptr;
}
void While::dump() const
{
    std::cout << "Node While " << std::endl;
    scope->dump();
}
While::~While()
{
    if (op && typeid(Decl) != typeid(*op))
        delete op;
    delete scope;
}

RType If::calc()
{
    if (op->calc())
        scope->calc();

    return 0;
}
llvm::Value *If::codegen() {
    return nullptr;
}
void If::dump() const
{
    std::cout << "Node If " << std::endl;
    scope->dump();
}
If::~If() 
{ 
    if (op && typeid(Decl) != typeid(*op))
        delete op;
    delete scope;
}
static llvm::Function *createMainFunction(Scope *begin);

void InitModule(Scope *begin) {
  std::cout << "I am here\n";
  TheModule = std::make_unique<llvm::Module>("my cool jit", TheContext);
  createMainFunction(begin);
}


static llvm::Function *proto() {
  llvm::FunctionType *FT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::InternalLinkage, "main", TheModule.get());
  return F;
}

llvm::Function *createMainFunction(Scope *begin) {

  llvm::Function *F = proto();

  // Create a new basic block to start insertion into.
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", F);
  Builder.SetInsertPoint(BB);
  Builder.CreateRet(llvm::ConstantInt::get(TheContext, llvm::APInt(32, 0)));

  begin->codegen();
  llvm::verifyFunction(*F);

  return F;
}

static void InitializeModule() {
}