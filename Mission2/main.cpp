#include <iostream>
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>

struct IEngine {
    virtual void Type() const = 0;
    virtual ~IEngine() = default;
};
struct IBrake {
    virtual void Type() const = 0;
    virtual ~IBrake() = default;
};
struct ISteering {
    virtual void Type() const = 0;
    virtual ~ISteering() = default;
};

struct GM_Engine : IEngine {
    void Type() const override { std::cout << " GM 엔진을 선택하셨습니다!\n"; }
};
struct ToyoTa_Engine : IEngine {
    void Type() const override { std::cout << " ToyoTa 엔진을 선택하셨습니다 .\n"; }
};
struct WIA_Engine : IEngine {
    void Type() const override { std::cout << " WIA 엔진을 선택하셨습니다 .\n"; }
};

struct MANDOBrake : IBrake {
    void Type() const override { std::cout << " Mando 제동장치를 선택하셨습니다.\n"; }
};
struct ContinentalBrake : IBrake {
    void Type() const override { std::cout << " Continental 제동장치를 선택하셨습니다.\n"; }
};
struct BoschBrake : IBrake {
    void Type() const override { std::cout << " Bosch 제동장치를 선택하셨습니다.\n"; }
};

struct BoschSteering : ISteering {
    void Type() const override { std::cout << " Bosch 조향장치를 선택하셨습니다.\n"; }
};
struct MobisSteering : ISteering {
    void Type() const override { std::cout << " Mobis 조향장치를 선택하셨습니다.\n"; }
};

template<typename T>
class Registry {
    std::unordered_map<std::string, std::function<std::unique_ptr<T>()>> creators;
public:
    void registerType(const std::string& name, std::function<std::unique_ptr<T>()> func) {
        creators[name] = func;
    }

    std::unique_ptr<T> create(const std::string& name) const {
        int answer = stoi(name, nullptr, 10);
        auto it = creators.begin();
        for (int idx = 0; idx < answer-1; idx++)
            it++;
        if (it != creators.end()) return it->second();
        throw std::runtime_error(" Unknown type: " + name);
    }

    void listOptions() const {
        for (const auto& [k, _] : creators) {
            std::cout << "- " << k << "\n";
        }
    }
};

class Car {
    std::unique_ptr<IEngine> engine_;
    std::unique_ptr<IBrake> brake_;
    std::unique_ptr<ISteering> steering_;
public:
    Car(std::unique_ptr<IEngine> e, std::unique_ptr<IBrake> b, std::unique_ptr<ISteering> s)
        : engine_(std::move(e)), brake_(std::move(b)), steering_(std::move(s)) {
             
    }

    void run() const {
        engine_->Type();
        steering_->Type();
        brake_->Type();
    }
};

class CarAssembler {
    Registry<IEngine> engineRegistry_;
    Registry<IBrake> brakeRegistry_;
    Registry<ISteering> steeringRegistry_;
public:
    CarAssembler() {
        engineRegistry_.registerType("1. GM", [] { return std::make_unique<GM_Engine>(); });
        engineRegistry_.registerType("2. TOYOTA", [] { return std::make_unique<ToyoTa_Engine>(); });
        engineRegistry_.registerType("3. WIA", [] { return std::make_unique<WIA_Engine>(); });


        brakeRegistry_.registerType("1. MANDO", [] { return std::make_unique<MANDOBrake>(); });
        brakeRegistry_.registerType("2. Continental", [] { return std::make_unique<ContinentalBrake>(); });
        brakeRegistry_.registerType("3. Bosch", [] { return std::make_unique<BoschBrake>(); });

        steeringRegistry_.registerType("1. Bosch", [] { return std::make_unique<BoschSteering>(); });
        steeringRegistry_.registerType("2. Mobis", [] { return std::make_unique<MobisSteering>(); });
    }

    Car assembleFromConsole() {
        std::string eng, brk, steer;

        std::cout << "어떤 엔진을 탑재할까요?\n"; engineRegistry_.listOptions(); std::cout << "> "; std::cin >> eng;
        std::cout << "어떤 제동장치를 선택할까요?\n";  brakeRegistry_.listOptions(); std::cout << "> "; std::cin >> brk;
        std::cout << "어떤 조향장치를 선택할까요?\n"; steeringRegistry_.listOptions(); std::cout << "> "; std::cin >> steer;

        return Car(
            engineRegistry_.create(eng),
            brakeRegistry_.create(brk),
            steeringRegistry_.create(steer)
        );
    }
};

int main() {
    try {
        CarAssembler assembler;
        Car car = assembler.assembleFromConsole();

        car.run();
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << "\n";
    }
    return 0;
}
