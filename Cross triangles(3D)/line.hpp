
template <typename T>
bool Line<T>::isAcross(Line<T> line, Vertex2D<T> & out) const
{
    PointParams<T> params = line.isSegmentsAcross(*this);

    if (isSegmentsAcross(line).status == PointParams<T>::PointStatus::OneSide)
        return false;
    if (params.status == PointParams<T>::PointStatus::OneSide)
        return false;

    // параллельность отрезков
    if (params.status == PointParams<T>::PointStatus::Parallel)
    {

        if (lengh() > line.lengh())
            return lineInLine(line, out);
        else 
            return line.lineInLine(*this, out);
 
        out = a;

        return true;
    }

    out.x = line.a.x + (line.b.x - line.a.x) * fabs(params.angle1) / fabs(params.angle2 - params.angle1);
    out.y = line.a.y + (line.b.y - line.a.y) * fabs(params.angle1) / fabs(params.angle2 - params.angle1);

    return true;
}

template <typename T>
PointParams<T> Line<T>::isSegmentsAcross(const Line<T> & line) const
{
    PointParams<T> params;

    T angle1 = Vector2D<T>(line.a, a) * Vector2D<T>(line.a, line.b);
    T angle2 = Vector2D<T>(line.a, b) * Vector2D<T>(line.a, line.b); 

    // Если точки одного отрезка лежат по одну сторону от другого отрезка\
    то они не пересекаюся
    if (angle1 * angle2 > 0)
    { 
        params.status = PointParams<T>::PointStatus::OneSide; 
        return params;
    }

    if (angle1 == 0 && angle2 == 0)
    {
        params.status = PointParams<T>::PointStatus::Parallel;
        return params;
    }

    params.status = PointParams<T>::PointStatus::DifferentSide;
    params.angle1 = angle1;
    params.angle2 = angle2;
    return params;
}

template <typename T>
bool Line<T>::lineInLine(Line<T> what, Vertex2D<T> & out) const
{
    T x1 = std::max(a.x, b.x);
    T x2 = std::min(a.x, b.x);
    if (what.a.x <= x1 && what.a.x >= x2)
    {
        out.x = what.a.x;
        out.y = what.a.y;
        return true;
    }
    if (what.b.x <= x1 && what.b.x >= x2)
    {
        out.x = what.b.x;
        out.y = what.b.y;
        return true;
    }
    return false;
}
