#include "RandomEvent.h"
// НЕ НУЖНО включать VirtualPet.h - избегаем циклической зависимости

RandomEvent::RandomEvent() : eventsTriggered(0) {
    // ПОЛОЖИТЕЛЬНЫЕ СОБЫТИЯ
    events.push_back({
        "Щедрый сосед",
        "Сосед угостил питомца вкусняшками!",
        -30, 0, 5, 15, 10
        });
    events.push_back({
        "Находка в парке",
        "Питомец нашёл потерянную игрушку!",
        0, -10, 0, 20, 15
        });
    events.push_back({
        "Солнечный день",
        "Хорошая погода подняла настроение!",
        0, -15, 5, 10, 5
        });
    events.push_back({
        "Подарок от друга",
        "Друг прислал посылку с кормом!",
        -40, 0, 0, 10, 0
        });
    events.push_back({
        "Удачная тренировка",
        "Питомец освоил новый трюк!",
        -10, -20, 0, 15, 25
        });
    events.push_back({
        "Лотерея выигрыш",
        "Вы выиграли 500 монет в лотерею!",
        0, 0, 0, 25, 30
        });
    events.push_back({
        "Встреча с чемпионом",
        "Известный тренер похвалил питомца!",
        0, 0, 5, 20, 20
        });
    events.push_back({
        "Магазин скидок",
        "Скидка 50% на все товары!",
        -20, 0, 0, 10, 0
        });
    events.push_back({
        "Новый друг",
        "Питомец нашёл нового друга!",
        0, -5, 0, 30, 15
        });
    events.push_back({
        "День рождения",
        "У питомца день рождения!",
        -25, -10, 10, 40, 50
        });

    // ОТРИЦАТЕЛЬНЫЕ СОБЫТИЯ
    events.push_back({
        "Дождливая погода",
        "Плохая погода испортила настроение",
        5, 10, -5, -15, 0
        });
    events.push_back({
        "Потерянная игрушка",
        "Любимая игрушка потерялась",
        0, 5, 0, -20, 0
        });
    events.push_back({
        "Визит к ветеринару",
        "Плановый осмотр у врача",
        0, -30, 5, -10, 10
        });
    events.push_back({
        "Голодный день",
        "Корм закончился раньше времени",
        25, 5, -5, -15, 0
        });
    events.push_back({
        "Бессонная ночь",
        "Питомец плохо спал ночью",
        5, 25, -5, -10, 0
        });
    events.push_back({
        "Ссора с соседом",
        "Соседский кот украл корм",
        20, 0, 0, -25, 0
        });
    events.push_back({
        "Простуда",
        "Питомец немного простудился",
        5, 10, -15, -10, 0
        });
    events.push_back({
        "Скучный день",
        "Ничего интересного не произошло",
        5, 5, 0, -10, 0
        });

    // НЕЙТРАЛЬНЫЕ СОБЫТИЯ
    events.push_back({
        "Обычный день",
        "Ничего особенного не случилось",
        5, 5, 0, 0, 5
        });
    events.push_back({
        "Прогулка",
        "Обычная прогулка во дворе",
        -5, -10, 0, 5, 10
        });
    events.push_back({
        "Дремота",
        "Питомец дремал весь день",
        5, -20, 0, 0, 5
        });
}

bool RandomEvent::trigger(PetBase& pet) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> chanceDist(1, 100);

    int chance = chanceDist(gen);
    if (chance > 30) {
        return false;
    }

    std::uniform_int_distribution<> eventDist(0, events.size() - 1);
    int eventIndex = eventDist(gen);
    const GameEvent& event = events[eventIndex];

    pet.getParameters().setHunger(
        pet.getParameters().getHunger() + event.hungerChange
    );
    pet.getParameters().setFatigue(
        pet.getParameters().getFatigue() + event.fatigueChange
    );
    pet.getParameters().setHealth(
        pet.getParameters().getHealth() + event.healthChange
    );
    pet.getParameters().setMood(
        pet.getParameters().getMood() + event.moodChange
    );

    // ИСПРАВЛЕНО: просто вызываем виртуальный метод
    if (event.xpChange > 0) {
        pet.addXP(event.xpChange);  // Работает для всех типов питомцев
    }

    std::cout << "\n";
    std::cout << "************************************************\n";
    std::cout << "*              СЛУЧАЙНОЕ СОБЫТИЕ!              *\n";
    std::cout << "************************************************\n";
    std::cout << "* " << event.name << "\n";
    std::cout << "*----------------------------------------------*\n";
    std::cout << "* " << event.description << "\n";

    if (event.hungerChange != 0) {
        std::cout << "* Голод: " << (event.hungerChange > 0 ? "+" : "")
            << event.hungerChange << "\n";
    }
    if (event.fatigueChange != 0) {
        std::cout << "* Усталость: " << (event.fatigueChange > 0 ? "+" : "")
            << event.fatigueChange << "\n";
    }
    if (event.healthChange != 0) {
        std::cout << "* Здоровье: " << (event.healthChange > 0 ? "+" : "")
            << event.healthChange << "\n";
    }
    if (event.moodChange != 0) {
        std::cout << "* Настроение: " << (event.moodChange > 0 ? "+" : "")
            << event.moodChange << "\n";
    }
    if (event.xpChange > 0) {
        std::cout << "* Опыт: +" << event.xpChange << "\n";
    }

    std::cout << "************************************************\n";

    eventsTriggered++;
    return true;
}

void RandomEvent::showEventLog() const {
    std::cout << "\n************************************************\n";
    std::cout << "*           Журнал событий                     *\n";
    std::cout << "************************************************\n";
    std::cout << "* Всего событий произошло: " << eventsTriggered << "              *\n";
    std::cout << "************************************************\n";
}