#include "stdafx.h"
#include "Utils.h"

std::random_device Utils::rd;
std::mt19937 Utils::gen;

void Utils::Init()
{
    gen.seed(rd());
}

float Utils::RandomValue()
{
    std::uniform_real_distribution<float> dist(0.f, 1.f);
    return dist(gen);
}

int Utils::RandomRange(int min, int maxExclude)
{
    std::uniform_int_distribution<int> dist(min, maxExclude - 1);
	return dist(gen);
}

float Utils::RandomRange(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins preset, const sf::FloatRect rect)
{
    sf::Vector2f newOrigin(rect.width, rect.height);
    newOrigin.x *= ((int)preset % 3) * 0.5f;
    newOrigin.y *= ((int)preset / 3) * 0.5f;
    obj.setOrigin(newOrigin);
    return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins preset)
{
    return SetOrigin(obj, preset, obj.getLocalBounds());
}

float Utils::Clamp(float value, float min, float max)
{
    if (value < min)
    {
        return min;
    }
    else if(value > max)
    {
        return max;
    }

    return value;
}

float Utils::Clamp01(float value)
{
    return Clamp(value, 0.f, 1.f);
}

float Utils::Magnitude(const sf::Vector2f& vec)
{
    return std::sqrtf(SqrMagnitude(vec));
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

sf::Vector2f Utils::GetNormal(const sf::Vector2f& vec)
{
    float mag = Utils::Magnitude(vec); //벡터의 길이 저장

    //float는 부정확한 값이다.
    //std::numeric_limits<float>::epsilon : float 수치 데이터에서 가장 작은 값이 반환되는 함수다.
    //0으로 나누지 못하게 예외처리
    if (mag < std::numeric_limits<float>::epsilon())
    {
        return { 0.f, 0.f };
    }

    return vec / mag;
}

void Utils::Normalize(sf::Vector2f& vec)
{
    float mag = Utils::Magnitude(vec); //벡터의 길이 저장
    if (mag > std::numeric_limits<float>::epsilon())
    {
        //0이 아닐 때
        vec = vec / mag; //길이가 1이 된다.
    }
}

//거리만 나오고 방향은 알 수 없다.
float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    //두 벡터 차에서 나온 벡터의 길이 : 두 점 사이의 거리
    return Utils::Magnitude(p1 - p2);
}

float Utils::Lerp(float min, float max, float t, bool clamp)
{
    if (clamp)
    {
        t = Utils::Clamp01(t); //0 또는 1값을 반환한다.
    }

    //min + (max - min) * t
    //max - min : 최대와 최소의 간격
    //* t : 간격의 비율을 곱한 값이 나온다.
    //min + : 최소에 더하면 최소부터 비율이 적용된 값, 즉 t비율의 값만큼의 값이 반환된다.
    return min + (max - min) * t;
}

//벡터값 보간에 사용
sf::Vector2f Utils::Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float t, bool clamp)
{
    if (clamp)
    {
        t = Utils::Clamp01(t); //0 또는 1값을 반환한다.
    }

    return min + (max - min) * t;
}

//색상 보간에 사용 / 색상 전환, 페이드 효과 등..
sf::Color Utils::Lerp(const sf::Color& min, const sf::Color& max, float t, bool clamp)
{
    if (clamp)
    {
        t = Utils::Clamp01(t); //0 또는 1값을 반환한다.
    }

    return sf::Color(
        (sf::Uint8)Lerp(min.r, max.r, t), 
        (sf::Uint8)Lerp(min.g, max.g, t), 
        (sf::Uint8)Lerp(min.b, max.b, t), 
        (sf::Uint8)Lerp(min.a, max.a, t)
    );
}
