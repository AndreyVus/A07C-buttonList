#include <iostream>
#include <vector>

class Button
{
public:
    int32_t id{};
    bool zustand{false};
    uint8_t gruppe{};          // 0 oder 1

    Button(int32_t i, uint8_t g) : id(i), gruppe(g) {}

    bool click(std::vector<Button>& alleButtons,
               int32_t& letzteAktivGruppe0,
               int32_t& letzteAktivGruppe1);
};

bool Button::click(std::vector<Button>& alleButtons,
                   int32_t& letzteAktivGruppe0,
                   int32_t& letzteAktivGruppe1)
{
    int32_t& refLetzte = (this->gruppe == 0) ? letzteAktivGruppe0
                                             : letzteAktivGruppe1;

    if (this->zustand) {                 // 1. Regel: aktiver Button → abschalten
        this->zustand = false;
        refLetzte = -1;                  // Gruppe hat keinen aktiven Button
        return false;
    }

    // 2. Alle anderen Buttons der Gruppe ausschalten
    for (auto& b : alleButtons)
        if (b.gruppe == this->gruppe)
            b.zustand = false;

    // 3. Diesen Button einschalten
    this->zustand = true;
    refLetzte = this->id;
    return true;
}

int main()
{
    std::vector<Button> buttons;
    int32_t a = -1;   // Gruppe 0
    int32_t b = -1;   // Gruppe 1

    // 2 Gruppen à 4 Buttons (ID 0..3 → Gruppe 0, 4..7 → Gruppe 1)
    for (int i = 0; i < 8; ++i)
        buttons.emplace_back(i, i < 4 ? 0 : 1);

    // Demo
    buttons[2].click(buttons, a, b);   // Gruppe 0: 2 aktiv
    std::cout << "a=" << a << "  b=" << b << '\n';

    buttons[5].click(buttons, a, b); // Gruppe 1: 5 aktiv
    std::cout << "a=" << a << "  b=" << b << '\n';

    buttons[2].click(buttons, a, b); // 2 nochmal → deaktiviert
    std::cout << "a=" << a << "  b=" << b << '\n';
}
