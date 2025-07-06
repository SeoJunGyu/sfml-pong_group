#pragma once
#include "GameObject.h"
class UiHud :
    public GameObject
{
protected:
    sf::Text textScore;
    sf::Text textScore1;
    sf::Text textScore2;
    sf::Text textMessage;

    std::string fontId; //텍스트 폰트
    bool isShowMessage;
    bool isWin;

    bool isDuo = false;

    int score = 0;
    int score1 = 0;
    int score2 = 0;

public:
    UiHud(const std::string& name = "");
    ~UiHud() override = default;

    void SetDuo(bool duo) { isDuo = duo; }

    void SetScore(int score);
    int GetScore() const { return score; }
    void SetScore1(int score);
    int GetScore1() const { return score1; }
    void SetScore2(int score);
    int GetScore2() const { return score2; }
    void SetMessage(const std::string& msg);
    void SetShowMessage(bool show) { isShowMessage = show; }
    bool GetShowMessage() const { return isShowMessage; }
    void SetWin(bool win) { isWin = win; }

    // GameObject을(를) 통해 상속됨
    void Init() override;

    void Release() override;

    void Reset() override;

    void Update(float dt) override;

    void Draw(sf::RenderWindow& window) override;

};

