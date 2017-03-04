namespace coffee
{
namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< typename type >
    Bezier< type >::Bezier()
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Bezier< type >::Bezier(const type& p0, const type& p1, const type& p2, const type& p3) :
        _P0(p0),
        _P1(p1),
        _P2(p2),
        _P3(p3)
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    template< typename type >
    real Bezier< type >::GetLength(uint32 precision) const
    {
        real length(0.0f);
        type begin = GetPoint(0.0f);
        for (uint32 step=0; step<precision; ++step)
        {
            type p = GetPoint((step+1.0f)/precision);
            length += (p-begin).GetNorm();
            begin = p;
        }
        return length;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type Bezier< type >::GetPoint(real time) const
    {
        Clamp(time, 0.0f, 1.0f);
        type point;
        point = _P0-_P1*3.0f+_P2*3.0f-_P3;
        point *= 1.0f-time;
        point += _P1*3.0f-_P2*6.0f+_P3*3.0f;
        point *= 1.0f-time;
        point += _P2*3.0f-_P3*3.0f;
        point *= 1.0f-time;
        point += _P3;
        return point;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type Bezier< type >::GetTangent(real time) const
    {
        Clamp(time, 0.0f, 1.0f);
        type tangent;
        tangent = _P0*3.0f-_P1*9.0f+_P2*9.0f-_P3*3.0f;
        tangent *= 1.0f-time;
        tangent += _P1*6.0f-_P2*12.0f+_P3*6.0f;
        tangent *= 1.0f-time;
        tangent += _P2*3.0f-_P3*3.0f;
        tangent.Normalize();
        return tangent;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    real Bezier< type >::GetNearestTime(const type& point, uint32 precision) const
    {
        float time(0.0f);
        real minimum(RealMaximumValue);        
        for (uint32 step=0 ; step<precision ; ++step)
        {
            float t = step/(precision-1.0f);
            type p = GetPoint(t);
            float distance = (point-p).GetNorm();
            if (distance<minimum)
            {
                minimum = distance;
                time = t;
            }
        }
        return time;
    }

}
}

