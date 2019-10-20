

namespace Global
{
    template <typename T>
    Vertex2D<T> center;
}

template <typename T>
Polygon<T>::Polygon(const std::vector<Vertex2D<T>> & vertex_ins)
{
    for (auto const & x : vertex_ins)
        vert_array.push_back(x);
}

template <typename T>
void Polygon<T>::push_back(const Vertex2D<T> & vert_ins)
{
    bool is = false;
    for (auto const & vert : vert_array)
    {
        if (vert == vert_ins)
        {
            is = true;
            break;
        }
    }
    if (!is)
        vert_array.push_back(vert_ins);
}

template <typename T>
T Polygon<T>::solveSquare()
{
    Global::center<T> = calcCenter();

    // Сортировка вершин многоугольника, чтобы можно было совершить их обход против часовой стрелки
    sort(vert_array.begin(), vert_array.end(), compare);

    T square = 0;

    // расчёт площади выпуклого многоугольника s = sum(Xi * Yi+1 - Xi+1 * Yi)
    for (int i = 0; i < vert_array.size(); i++)
    {
        square += vert_array[i].x * vert_array[(i + 1) % vert_array.size()].y - vert_array[(i + 1) % vert_array.size()].x * vert_array[i].y;
    }

    return fabs(square) / 2;
}

template <typename T>
bool Polygon<T>::compare(const Vertex2D<T> & a, const Vertex2D<T> & b)
{
    if (getAngle(a) > getAngle(b))
        return 1;
            
    return 0;
}   

template <typename T>
T Polygon<T>::getAngle(const Vertex2D<T> & a)
{
    T dx_a = 0, dy_a = 0, r_a = 0, cosA = 0, sinA = 0;
    dx_a = a.x - Global::center<T>.x;
    dy_a = a.y - Global::center<T>.y;

    T b = dx_a * dx_a + dy_a * dy_a;

    r_a = sqrtl(b);

    cosA = dx_a / r_a;
    sinA = dy_a / r_a;

    if (sinA > 0)
        return acosf(cosA);
    else
        return (2 * PI - acosf(cosA));
}

template <typename T>
Vertex2D<T> Polygon<T>::calcCenter() const
{
    T x = 0;
    T y = 0;
    T kx = 0, ky = 0;

    for (auto const & vert : vert_array)
    {
        x += vert.x;
        y += vert.y;

        kx += 1; ky += 1;        
    }
    
    return Vertex2D<T>(x / kx, y / ky);
}