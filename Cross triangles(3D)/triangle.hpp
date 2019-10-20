

template <typename T>
Polygon<T> Triangle2D<T>::commonPolygon(Triangle2D<T> & triangle)
{
    Polygon<T> polygon;
    int out_count = 0;

    // поиск всех точек пересечения 
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            Vertex2D<T> cross(0, 0); // outer vertex
            if (Line<T>(vertex[i], vertex[(i + 1) % 3]).isAcross(Line<T>(triangle[j], triangle[(j + 1) % 3]), cross))
            {
                out_count++;
                polygon.push_back(cross);
            }
        }
    // Добавление всех точек, которые лежат в другом треугольнике
    Internal(triangle, polygon);
 
    return polygon;
}

template <typename T>
void Triangle2D<T>::Internal(Triangle2D<T> & triangle, Polygon<T> & polygon)
{
    allInternalVertex2D(triangle, polygon);
    triangle.allInternalVertex2D(*this, polygon);
}

template <typename T>
void Triangle2D<T>::allInternalVertex2D(Triangle2D<T> & trianle, Polygon<T> & polygon)
{
    Vertex2D<T> A = vertex[0];
    Vertex2D<T> B = vertex[1];
    Vertex2D<T> C = vertex[2];

    T det = Vector2D<T>(A, B) * Vector2D<T>(A, C);

    for (int j = 0; j < 3; j++)
    {
        T det2 =  Vector2D<T>(A, trianle[j]) * Vector2D<T>(A, C);
        T det1 = Vector2D<T>(A, B) * Vector2D<T>(A, trianle[j]);

        T det3 = det - det1 - det2;
        
        if (!((det2 > 0 && det1 > 0 && det3 > 0) || (det2 < 0 && det1 < 0 && det3 < 0)))
            continue;


        polygon.push_back(trianle[j]);
    }
}

template <typename T>
bool Triangle3D<T>::isAcross(const Triangle3D<T> & triangle) const
{
    if (hasInternal(triangle) || triangle.hasInternal(*this))
       return true;

    return intersects(triangle);
}

template <typename T>
bool Triangle3D<T>::hasInternal(const Triangle3D<T> & trianle) const
{
    const Vertex3D<T> A = vertex[0];
    const Vertex3D<T> B = vertex[1];
    const Vertex3D<T> C = vertex[2];

    Vector3D<T> crossProd = Vector3D<T>(A, B).cross(Vector3D<T>(A, C));
    const T det = sqrtl(crossProd.dot(crossProd));
    if (det == 0) return false;

    for (int j = 0; j < 3; j++)
    {

        crossProd =  Vector3D<T>(A, trianle[j]).cross(Vector3D<T>(A, C));
        const T det2 = sqrtl(crossProd.dot(crossProd));

        crossProd = Vector3D<T>(A, B).cross(Vector3D<T>(A, trianle[j]));
        const T det1 = sqrtl(crossProd.dot(crossProd));

        crossProd = Vector3D<T>(trianle[j], B).cross(Vector3D<T>(trianle[j], C));
        const T det3 = sqrtl(crossProd.dot(crossProd));
        
        if ((det1 + det2 + det3) != det)
            continue;

        return true;
    }

    return false;
}

template <typename T>
bool Triangle3D<T>::intersects(const Triangle3D<T> & triangle) const
{
    Vector3D<T> e1 = vertex[1] - vertex[0];
    Vector3D<T> e2 = vertex[2] - vertex[0];

    Vector3D<T> n1 = e1.cross(e2).norm();

    if (n1.length() == 0)
    {
        return false;

        // TODO check if 2 lines intersect!
    }

    Vector3D<T> n2 = e1.cross(n1).norm();

    Triangle2D<T> first = getProection(e1, n2, vertex[0]);
    Triangle2D<T> second = triangle.getProection(e1, n2, vertex[0]);
    if (first.commonPolygon(second).Size() == 0)
        return false;
    
    first = getProection(e1, n1, vertex[0]);
    second = triangle.getProection(e1, n1, vertex[0]);
    if (first.commonPolygon(second).Size() == 0)
        return false;

    first = getProection(n1, n2, vertex[0]);
    second = triangle.getProection(n1, n2, vertex[0]);
    if (first.commonPolygon(second).Size() == 0)
        return false;


    // new point
    e1 = vertex[0] - vertex[1];
    e2 = vertex[2] - vertex[1];

    n1 = e2.cross(e1);
    n2 = n1.cross(e2);

    first = getProection(n1, n2, vertex[1]);
    second = triangle.getProection(n1, n2, vertex[1]);
    if (first.commonPolygon(second).Size() == 0)
        return false;

    return true;
}

template <typename T>
Triangle2D<T> Triangle3D<T>::getProection(Vector3D<T> const & e1, Vector3D<T> const & e2, Vertex3D<T> const & center) const
{
    Triangle2D<T> triangle;
    for (int i = 0; i < 3; i++)
        triangle[i] = Vertex2D<T>((vertex[i] - center).dot(e1), (vertex[i] - center).dot(e2));

    return triangle;

}