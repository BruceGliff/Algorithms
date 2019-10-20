

namespace Optimization{

template <typename T>
Box<T>::Box(const Box<T> & box, int iter)
{
    int k = (iter&4) >> 2;
    int j = (iter&2) >> 1;
    int i = iter&1;

    
    zero = Vertex3D<T>(box.zero.x + T(i) * (box.zero.x + box.d) / 2,
                 box.zero.y + T(j) * (box.zero.y + box.d) / 2,
                 box.zero.z + T(k) * (box.zero.z + box.d) / 2);
    d = box.d / 2;
}

template <typename T>
void Sphere<T>::SetSphere()
{
    const Vertex3D<T> A = triangle[0];
    const Vertex3D<T> B = triangle[1];
    const Vertex3D<T> C = triangle[2];

    center.x = (A.x + B.x + C.x) / 3;
    center.y = (A.y + B.y + C.y) / 3;
    center.z = (A.z + B.z + C.z) / 3;

    radius = 0;
    for(int i = 0; i < 3; i++)
    {
        T f = Vector3D<T>((triangle[i]), center).length();
        if (f > radius)
            radius = f;
    }
}

template <typename T>
void CreateBox(const Box<T> & box, std::vector<Sphere<T>*> & array, int last_size, int delta_depth, std::set<int> & out_result)
{
    if (array.size() < 2)
        return;
    if (array.size() == 2)
    {
       array[0]->CheckTriangles(array[1], out_result);
       return;
    }

    if (last_size == array.size())
        delta_depth++;
    else 
        delta_depth = 0;

    if (delta_depth == 8)
    {
        for(int i = 0; i < array.size() - 1; i++)
            for (int j = i + 1; j < array.size(); j++)
                array[i]->CheckTriangles(array[j], out_result);
        return;
    }       

    std::array<std::vector<Sphere<T>*>, 8> mas;
    for (auto i = array.begin(); i < array.end(); i++)
    {
        for (int iter = 0; iter < 8; iter++)
        {   
            Box<T> New = Box<T>(box, iter);

            if (!((*i)->insideBox(New)))
                continue;

            if ((*i)->SphereIntersectBox(New))
            {
                int del2 = 0;
                for (auto j = i; j < array.end(); j++)
                {
                    if (i == j) continue;
                    (*i)->CheckTriangles((*j), out_result);
                }

                delete (*i);
                array.erase(i);
                i--;
                break;
            }    
                
            mas[iter].push_back(*i);
        }
    }
    for (int i = 0; i < 8; i++)
        Optimization::CreateBox(Box<T>(box, i), mas[i], array.size(), delta_depth, out_result);
}

}