#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

struct CarInformation
{
    int CarType;
    int EngineType;
    int BrakeSystem;
    int SteeringSystem;
};
void PrintCarType();
void selectCarType(int answer);

void PrintCarEngine();
void selectEngine(int answer);

void PrintCarBrakeSystem();
void selectbrakeSystem(int answer);

void PrintCarSteeringSystem();
void selectSteeringSystem(int answer);

void PrintCarRunTest();
int SelectCarRunTest(const CarInformation car);

void delay(int ms);
int ReceiveAnswer();
bool isValidCheckofSEDAN(const CarInformation car);
bool isValidCheckofSUV(const CarInformation car);
bool isValidCheckofTRUCK(const CarInformation car);
bool isValidCheckofMANDO(const CarInformation car);
bool isValidCheck(const CarInformation car);
bool isTestCheck(const CarInformation car);

enum QuesionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test
};

enum CarType
{
    Init_CarType,
    SEDAN = 1,
    SUV,
    TRUCK,
    MAX_CARTYPE
};
char stCarType[MAX_CARTYPE-1][20]
{
    {"SEDAN"},
    {"SUV"},
    {"TRUCK"}
};

enum Engine
{
    Init_Engine,
    GM = 1,
    TOYOTA,
    WIA,
    BROKEN,
    MAX_Engine
};
char stEngine[MAX_Engine - 1][20]
{
    {"GM"},
    {"TOYOTA"},
    {"WIA"}
};
enum brakeSystem
{
    Init_BrakeSystem,
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    MAX_BrakeSystem
};
char stbrakeSystem[MAX_BrakeSystem - 1][20]
{
    {"MANDO"},
    {"CONTINENTAL"},
    {"BOSCH_B"}
};
enum SteeringSystem
{
    Init_SteeringSystem,
    BOSCH_S = 1,
    MOBIS,
    MAX_SteeringSystem
};
char stSteeringSystem[MAX_SteeringSystem - 1][10]
{
    {"BOSCH_S"},
    {"MOBIS"}
};
void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

//todo 
// 입력 부분에서 0이랑 exit 처리

void PrintCarType()
{
    printf(CLEAR_SCREEN);

    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");

}

int SelectCarType(CarInformation* car)
{
    int answer;
    answer = ReceiveAnswer();
    if (!(answer > Init_CarType && answer <= MAX_CARTYPE))
    {
        printf("ERROR :: 차량 타입은 %d ~ %d 범위만 선택 가능\n", Init_CarType+1, MAX_CARTYPE-1);
        delay(800);
        return CarType_Q;
    }
   
   
    printf("차량 타입으로 %s을 선택하셨습니다.\n", stCarType[answer-1]);

    car->CarType = answer;

    return Engine_Q;
}

void PrintCarEngine()
{
    printf(CLEAR_SCREEN);
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");

}
int SelectCarEngine(CarInformation* car)
{
    int answer;
    answer = ReceiveAnswer();

    if(answer == 0)
        return CarType_Q;

    if (!(answer > Init_Engine && answer <= MAX_Engine))
    {
        printf("ERROR :: 엔진은 %d ~ %d 범위만 선택 가능\n", Init_Engine+1, MAX_Engine-1);
        delay(800);
        return Engine_Q;
    }

    printf("%s 엔진을 선택하셨습니다.\n",stEngine[answer-1]);
   
    car->EngineType = answer;

    return brakeSystem_Q;
}
void PrintCarBrakeSystem()
{
    printf(CLEAR_SCREEN);
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");

}

int SelectCarBrakeSystem(CarInformation* car)
{
    int answer;
    answer = ReceiveAnswer();

    if (answer == 0)
        return Engine_Q;

    if (!(answer > Init_BrakeSystem && answer <= MAX_BrakeSystem))
    {
        printf("ERROR :: 제동장치는 %d ~ %d 범위만 선택 가능\n", Init_BrakeSystem+1, MAX_BrakeSystem-1);
        delay(800);
        return brakeSystem_Q;
    }

    printf("%s  제동장치를 선택하셨습니다.\n",stbrakeSystem[answer - 1]);
   
    car->BrakeSystem = answer;

    return SteeringSystem_Q;
}
void PrintCarSteeringSystem()
{
    printf(CLEAR_SCREEN);
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}
int SelectCarSteeringSystem(CarInformation* car)
{
    int answer;
    answer = ReceiveAnswer();

    if (answer == 0)
        return brakeSystem_Q;

    if (!(answer > Init_SteeringSystem && answer <= MAX_SteeringSystem))
    {
        printf("ERROR :: 조향장치는 %d ~ %d 범위만 선택 가능\n", Init_SteeringSystem+1, MAX_SteeringSystem-1);
        delay(800);
        return SteeringSystem_Q;
    }

    printf("%s 조향장치 선택하셨습니다.\n",stSteeringSystem[answer-1]);

    car->SteeringSystem = answer;

    return Run_Test;
}
void PrintCarRunTest()
{
    printf(CLEAR_SCREEN);
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}
int SelectCarRunTest(const CarInformation car)
{
    int answer;
    answer = ReceiveAnswer();

    if (answer == 0)
        return CarType_Q;


    if (!(answer >= 1 && answer <= 2))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        delay(800);
        return Run_Test;;
    }

    if ( answer == 1)
    {
        
        if (true != isValidCheck(car))
        {
            printf("자동차가 동작되지 않습니다\n");
            return Run_Test;
        }
       
        if(BROKEN == car.EngineType)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
            return Run_Test;
        }
       
        printf("Car Type : %s\n",stCarType[car.CarType-1]);
        printf("Engine : %s\n", stEngine[car.EngineType - 1]);
        printf("Brake System : %s\n",stbrakeSystem[car.BrakeSystem-1]);
        printf("steering System : %s\n", stSteeringSystem[car.SteeringSystem - 1]);
        printf("자동차가 동작됩니다.\n");
                    
        delay(2000);

    }
    else if (answer == 2)
    {
        printf("Test...\n");
        delay(1500);     
        if (true == isTestCheck(car))
        {
            printf("자동차 부품 조합 테스트 결과 : PASS\n");
        }       
        delay(2000);

    }

    return Run_Test;
}
int ReceiveAnswer()
{
    char buf[100];
    printf("===============================\n");

    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("바이바이\n");
        exit(0);
    }
    //Remove Enter Opening Characters
    char* checkNumber;
    int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
    }
    return answer;
}


bool isValidCheckofSEDAN(const CarInformation car)
{
    if (car.BrakeSystem == CONTINENTAL)
    {
        return false;
    }
    return true;
}

bool isValidCheckofSUV(const CarInformation car)
{
    if (car.EngineType == TOYOTA)
    {
        return false;
    }
    return true;
}

bool isValidCheckofTRUCK(const CarInformation car)
{
    bool bret=true;
    if (car.EngineType == WIA)
    {
        bret = false;
    }
        
    if (car.BrakeSystem == MANDO)
    {
        bret = false;

    }

    return bret;
}
bool isValidCheckofBOSCH(const CarInformation car)
{
    if (car.BrakeSystem == BOSCH_B && car.SteeringSystem != BOSCH_S)
    {
        return false;
    }
    return true;
}

bool isValidCheck(const CarInformation car)
{
    switch (car.CarType)
    {
    case SEDAN:
        if (true != isValidCheckofSEDAN(car))
            return false;
        break;
    case SUV:
        if (true != isValidCheckofSUV(car))
            return false;
        break;
    case TRUCK:
        if (true != isValidCheckofTRUCK(car))
            return false;
        break;
    }

    if (true != isValidCheckofBOSCH(car))
        return false;

    return true;
}


bool isTestCheck(const CarInformation car)
{
    int ret = true;
    switch (car.CarType)
    {
    case SEDAN:
        if (true != isValidCheckofSEDAN(car))
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Sedan에는 Continental제동장치 사용 불가\n");
            ret = false;
        }
        break;
    case SUV:
        if (true != isValidCheckofSUV(car))
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("SUV에는 TOYOTA엔진 사용 불가\n");
            ret = false;

        }
        break;
    case TRUCK:
        if (true != isValidCheckofTRUCK(car))
        {
            if (car.EngineType == WIA)
            {
                 printf("자동차 부품 조합 테스트 결과 : FAIL\n");
                 printf("Truck에는 WIA엔진 사용 불가\n");
                 ret = false;

            }

            if (car.BrakeSystem == MANDO)
            {
                 printf("자동차 부품 조합 테스트 결과 : FAIL\n");
                 printf("Truck에는 Mando제동장치 사용 불가\n");
                 ret = false;

            }
        }          
        break;
    }

    if (true != isValidCheckofBOSCH(car))
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch엔진에는 BOSCH조향장치 이외 사용 불가\n");
        ret = false;

    }

    return ret;
}
int main()
{
    CarInformation mycar;
    int step = CarType_Q;
    int answer;
    while (1)
    {
        switch (step)
        {
        case CarType_Q:
            PrintCarType();
            step = SelectCarType(&mycar);
            break;
        case Engine_Q:
            PrintCarEngine();
            step = SelectCarEngine(&mycar);
            break;
        case brakeSystem_Q:
            PrintCarBrakeSystem();
            step = SelectCarBrakeSystem(&mycar);
            break;
        case SteeringSystem_Q:
            PrintCarSteeringSystem();
            step = SelectCarSteeringSystem(&mycar);
            break;
        case Run_Test:
            PrintCarRunTest();
            step = SelectCarRunTest(mycar);
            break;
        }
    }
}