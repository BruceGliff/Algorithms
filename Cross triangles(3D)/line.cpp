#include "line.h"

bool Line::isAcross(Line line, Vertex2D & out) const
{
    PointParams params = line.isSegmentsAcross(*this);

    if (isSegmentsAcross(line).status == PointParams::PointStatus::OneSide)
        return false;
    if (params.status == PointParams::PointStatus::OneSide)
        return false;

    // параллельность отрезков
    if (params.status == PointParams::PointStatus::Parallel)
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

PointParams Line::isSegmentsAcross(const Line & line) const
{
    PointParams params;

    float angle1 = Vector2D(line.a, a) * Vector2D(line.a, line.b);
    float angle2 = Vector2D(line.a, b) * Vector2D(line.a, line.b); 

    // Если точки одного отрезка лежат по одну сторону от другого отрезка\
    то они не пересекаюся
    if (angle1 * angle2 > 0)
    { 
        params.status = PointParams::PointStatus::OneSide; 
        return params;
    }

    if (angle1 == 0 && angle2 == 0)
    {
        params.status = PointParams::PointStatus::Parallel;
        return params;
    }

    params.status = PointParams::PointStatus::DifferentSide;
    params.angle1 = angle1;
    params.angle2 = angle2;
    return params;
}

bool Line::lineInLine(Line what, Vertex2D & out) const
{
    float x1 = std::max(a.x, b.x);
    float x2 = std::min(a.x, b.x);
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
