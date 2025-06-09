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
// �Է� �κп��� 0�̶� exit ó��

void PrintCarType()
{
    printf(CLEAR_SCREEN);

    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("� ���� Ÿ���� �����ұ��?\n");
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
        printf("ERROR :: ���� Ÿ���� %d ~ %d ������ ���� ����\n", Init_CarType+1, MAX_CARTYPE-1);
        delay(800);
        return CarType_Q;
    }
   
   
    printf("���� Ÿ������ %s�� �����ϼ̽��ϴ�.\n", stCarType[answer-1]);

    car->CarType = answer;

    return Engine_Q;
}

void PrintCarEngine()
{
    printf(CLEAR_SCREEN);
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. ���峭 ����\n");

}
int SelectCarEngine(CarInformation* car)
{
    int answer;
    answer = ReceiveAnswer();

    if(answer == 0)
        return CarType_Q;

    if (!(answer > Init_Engine && answer <= MAX_Engine))
    {
        printf("ERROR :: ������ %d ~ %d ������ ���� ����\n", Init_Engine+1, MAX_Engine-1);
        delay(800);
        return Engine_Q;
    }

    printf("%s ������ �����ϼ̽��ϴ�.\n",stEngine[answer-1]);
   
    car->EngineType = answer;

    return brakeSystem_Q;
}
void PrintCarBrakeSystem()
{
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
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
        printf("ERROR :: ������ġ�� %d ~ %d ������ ���� ����\n", Init_BrakeSystem+1, MAX_BrakeSystem-1);
        delay(800);
        return brakeSystem_Q;
    }

    printf("%s  ������ġ�� �����ϼ̽��ϴ�.\n",stbrakeSystem[answer - 1]);
   
    car->BrakeSystem = answer;

    return SteeringSystem_Q;
}
void PrintCarSteeringSystem()
{
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
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
        printf("ERROR :: ������ġ�� %d ~ %d ������ ���� ����\n", Init_SteeringSystem+1, MAX_SteeringSystem-1);
        delay(800);
        return SteeringSystem_Q;
    }

    printf("%s ������ġ �����ϼ̽��ϴ�.\n",stSteeringSystem[answer-1]);

    car->SteeringSystem = answer;

    return Run_Test;
}
void PrintCarRunTest()
{
    printf(CLEAR_SCREEN);
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
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
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        delay(800);
        return Run_Test;;
    }

    if ( answer == 1)
    {
        
        if (true != isValidCheck(car))
        {
            printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
            return Run_Test;
        }
       
        if(BROKEN == car.EngineType)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
            return Run_Test;
        }
       
        printf("Car Type : %s\n",stCarType[car.CarType-1]);
        printf("Engine : %s\n", stEngine[car.EngineType - 1]);
        printf("Brake System : %s\n",stbrakeSystem[car.BrakeSystem-1]);
        printf("steering System : %s\n", stSteeringSystem[car.SteeringSystem - 1]);
        printf("�ڵ����� ���۵˴ϴ�.\n");
                    
        delay(2000);

    }
    else if (answer == 2)
    {
        printf("Test...\n");
        delay(1500);     
        if (true == isTestCheck(car))
        {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
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

    // ���� ���๮�� ����
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("���̹���\n");
        exit(0);
    }
    //Remove Enter Opening Characters
    char* checkNumber;
    int answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

    // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
    if (*checkNumber != '\0')
    {
        printf("ERROR :: ���ڸ� �Է� ����\n");
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
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("Sedan���� Continental������ġ ��� �Ұ�\n");
            ret = false;
        }
        break;
    case SUV:
        if (true != isValidCheckofSUV(car))
        {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("SUV���� TOYOTA���� ��� �Ұ�\n");
            ret = false;

        }
        break;
    case TRUCK:
        if (true != isValidCheckofTRUCK(car))
        {
            if (car.EngineType == WIA)
            {
                 printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                 printf("Truck���� WIA���� ��� �Ұ�\n");
                 ret = false;

            }

            if (car.BrakeSystem == MANDO)
            {
                 printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                 printf("Truck���� Mando������ġ ��� �Ұ�\n");
                 ret = false;

            }
        }          
        break;
    }

    if (true != isValidCheckofBOSCH(car))
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch�������� BOSCH������ġ �̿� ��� �Ұ�\n");
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