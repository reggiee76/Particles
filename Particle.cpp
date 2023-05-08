#include "Particle.h"


bool Particle::almostEqual(double a, double b, double eps)
{
	return fabs(a - b) < eps;
}

void Particle::unitTests()
{
    int score = 0;

    cout << "Testing RotationMatrix constructor...";
    double theta = PI / 4.0;
    RotationMatrix r(PI / 4);
    if (r.getRows() == 2 && r.getCols() == 2 && almostEqual(r(0, 0), cos(theta))
        && almostEqual(r(0, 1), -sin(theta))
        && almostEqual(r(1, 0), sin(theta))
        && almostEqual(r(1, 1), cos(theta)))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing ScalingMatrix constructor...";
    ScalingMatrix s(1.5);
    if (s.getRows() == 2 && s.getCols() == 2
        && almostEqual(s(0, 0), 1.5)
        && almostEqual(s(0, 1), 0)
        && almostEqual(s(1, 0), 0)
        && almostEqual(s(1, 1), 1.5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing TranslationMatrix constructor...";
    TranslationMatrix t(5, -5, 3);
    if (t.getRows() == 2 && t.getCols() == 3
        && almostEqual(t(0, 0), 5)
        && almostEqual(t(1, 0), -5)
        && almostEqual(t(0, 1), 5)
        && almostEqual(t(1, 1), -5)
        && almostEqual(t(0, 2), 5)
        && almostEqual(t(1, 2), -5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    
    cout << "Testing Particles..." << endl;
    cout << "Testing Particle mapping to Cartesian origin..." << endl;
    if (m_centerCoordinate.x != 0 || m_centerCoordinate.y != 0)
    {
        cout << "Failed.  Expected (0,0).  Received: (" << m_centerCoordinate.x << "," << m_centerCoordinate.y << ")" << endl;
    }
    else
    {
        cout << "Passed.  +1" << endl;
        score++;
    }

    cout << "Applying one rotation of 90 degrees about the origin..." << endl;
    Matrix initialCoords = m_A;
    rotate(PI / 2.0);
    bool rotationPassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), -initialCoords(1, j)) || !almostEqual(m_A(1, j), initialCoords(0, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            rotationPassed = false;
        }
    }
    if (rotationPassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a scale of 0.5..." << endl;
    initialCoords = m_A;
    scale(0.5);
    bool scalePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 0.5 * initialCoords(0,j)) || !almostEqual(m_A(1, j), 0.5 * initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            scalePassed = false;
        }
    }
    if (scalePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a translation of (10, 5)..." << endl;
    initialCoords = m_A;
    translate(10, 5);
    bool translatePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 10 + initialCoords(0, j)) || !almostEqual(m_A(1, j), 5 + initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            translatePassed = false;
        }
    }
    if (translatePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Score: " << score << " / 7" << endl;
}

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) : m_A(2, numPoints)
{
    // Initialize m_ttl  to the global constant TTL, 
    // which gives it a time to live of 5 seconds
    m_ttl = TTL;

    // Initialize m_Points to numPoints
    m_numPoints = numPoints;


    // Initialize m_radiansPerSec to a random 
    // angular velocity in the range [0:PI]

    // m_cartesianPlane will be used to map between monitor coordinates 
    // and Cartesian coordinates that are centered about the origin (0,0)
    // so our Matrim_cartesianPlane will be used to map between monitor coordinates 
    // and Cartesian coordinates that are centered about the origin (0,0) so our 
    // Matrix algebra will work correctlyx algebra will work correctly
    
    // Call setCenter(0,0)


    // Call setSize(target.getSize().x, (-1.0) * target.getSize().y)
    // This will initialize its width and height to the size of the
    // RenderWindow stored in target and invert the y - axis
    

    // Store the location of the center of this particle on the Cartesian 
    // plane in m_centerCoordinate
    // ***
    // Use mapPixelToCoords with m_cartesianPlane to map mouseClickPosition to
    // the Cartesian plane and store it in m_centerCoordinate
    // ***


    // Assign m_vx and m_vy to random pixel velocities

    // Assign m_color1 and m_color2 to Colors
    
}

// This function overrides the virtual function from sf::Drawable to allow our draw
//  function to polymorph 
//
void Particle::draw(RenderTarget& target, RenderStates states) const
{
    VertexArray lines(TriangleFan, this->m_numPoints + 1);
    Vector2f center = target.mapCoordsToPixel(this->m_centerCoordinate);
    lines[0].position = center;
    lines[0].color = this->m_color1;
    for(int j = 1; j <= m_numPoints;j++){
        lines[j].position = target.mapCoordsToPixel(this->m_A[j-1]);
        lines[j].color = this->m_color2;
    }
}

void Particle::update(float dt)
{
    dt = m_ttl - dt;
    rotate(dt * m_radiansPerSec);
    scale(SCALE);
    
    float dx, dy;
    dx = vx * dt;

    vy = vy - (G * dt);

    dy = vy * dt;

    translate(dx, dy);
}


void Particle::rotate(double theta)
{
    Vector2f temp = m_centerCoordinate;
    this->translate(-m_centerCoordinate.x,-m_centerCoordinate.y);
    RotationMatrix r(theta);
    this->m_A = R * this->m_A;
    this->translate(temp.x,temp.y);
}

void Particle::scale(double c)
{
    // Store the value of m_centerCoordinate in a Vector2f temp
    Vector2f temp = m_centerCoordinate;

    // Shift back to the origin
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);

    // Construct a ScalingMatrix S with the specified scaling multiplier c
    ScalingMatrix S(c);

    // Multiply S by m_A
    this->m_A = S * this->m_A;

    // Shift back to the original center
    translate(temp.x, temp.y);
}

void Particle::translate(double xShift, double yShift)
{
    // TODO: TranslationMatrix T(xShift, yShift, nCols)
    TranslationMatrix T(xShift, yShift, m_A.getCols());
    m_A = T + m_A;

    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
}

