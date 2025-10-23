#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 1000

typedef struct {
    char date[11];
    char category[30];
    float amount;
} Expense;

Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

void loadExpenses(const char *filename)
{
    FILE *fin = fopen(filename, "r");
    if (!fin)
        return;

    while (expenseCount < MAX_EXPENSES &&
           fscanf(fin, "%10s %29s %f", expenses[expenseCount].date, expenses[expenseCount].category, &expenses[expenseCount].amount) == 3)
    {
        expenseCount++;
    }

    fclose(fin);
}

void saveExpenseToFile(const char *filename, Expense e)
{
    FILE *fout = fopen(filename, "a");
    if (!fout)
    {
        printf("Ошибка при сохранении файла!\n");
        return;
    }

    fprintf(fout, "%s %s %.2f\n", e.date, e.category, e.amount);

    fclose(fout);
}

void addExpense()
{
    if (expenseCount >= MAX_EXPENSES)
    {
        printf("Превышен лимит расходов!\n");
        return;
    }

    Expense e;

    printf("Введите дату (дд.мм.гггг): ");
    if (scanf("%10s", e.date) != 1) {
        printf("Ошибка ввода даты.\n");
        return;
    }

    printf("Введите категорию: ");
    if (scanf("%29s", e.category) != 1) {
        printf("Ошибка ввода категории.\n");
        return;
    }

    printf("Введите сумму: ");
    if (scanf("%f", &e.amount) != 1) {
        printf("Ошибка ввода суммы.\n");
        return;
    }

    expenses[expenseCount++] = e;
    saveExpenseToFile("expenses.txt", e);

    printf("Расход добавлен!\n");
}

void showAllExpenses()
{
    if (expenseCount == 0)
    {
        printf("Нет данных о расходах.\n");
        return;
    }

    printf("\n--- Все расходы ---\n");
    printf("%-12s%-15s%s\n", "Дата", "Категория", "Сумма");
    printf("------------------------------\n");

    for (int i = 0; i < expenseCount; i++)
    {
        printf("%-12s%-15s%.2f руб.\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }
}

void showStats()
{
    if (expenseCount == 0)
    {
        printf("Нет данных для анализа.\n");
        return;
    }

    float total = 0;
    float max = expenses[0].amount;

    for (int i = 0; i < expenseCount; i++)
    {
        total += expenses[i].amount;
        if (expenses[i].amount > max)
        {
            max = expenses[i].amount;
        }
    }

    float average = total / expenseCount;

    printf("\n--- Статистика ---\n");
    printf("Всего потрачено: %.2f руб.\n", total);
    printf("Средняя трата: %.2f руб.\n", average);
    printf("Максимальная трата: %.2f руб.\n", max);
}

void showMenu()
{
    printf("\n=== Трекер расходов ===\n");
    printf("1. Добавить расход\n");
    printf("2. Показать все расходы\n");
    printf("3. Показать статистику\n");
    printf("4. Выход\n");
    printf("Выберите пункт: ");
}

int main()
{
    loadExpenses("expenses.txt");

    int choice;

    do
    {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            // Clear invalid input
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Неверный выбор.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            addExpense();
            break;
        case 2:
            showAllExpenses();
            break;
        case 3:
            showStats();
            break;
        case 4:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор.\n");
        }

    } while (choice != 4);

    return 0;
}
