/*�C���]�p�����G
  1. �C���d��j�p�� 5X5
  2. �@���T���C�� (0, 1, 2)
  3. �N�T�Ӥ@�˰t��b�@�_�h�|����

  �{���]�p�����G
  1. �������Ыؤ@�� 5X5 ���d��
  2. �A��l�ƹC���ѽL
     �H�H�����srand(time(NULL));
     �N�ѽL���d�򤺶񺡤T���C�� (0, 1, 2)
  3. �ھڨϥΪ̿�J���y�ШӶi�沾��ss
  4. �L�{���N�T�ӭ��ƪ������A�ñN�W�謰����
     �����U�ӥH�񺡩��U�Ů�
  5. ��ѽL���S���ۦP���C��ɡA�h�|���X�C��
     �åN��C������
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_WIDTH 5  // y�̤j��5
#define BOARD_HEIGHT 5 // x�̤j��5
#define COLORS 3       // �T���C�� 0, 1, 2
#define MIN_MATCH 3    // �̤֤T�ӳs�u

// �w�q�C��
typedef struct
{
    int color;
} Block;

// �w�q�C���ѽL���c
typedef struct
{
    int width;
    int height;
    Block **board;
} GameBoard;

// �ЫعC���ѽL
GameBoard *createGameBoard(int width, int height)
{
    GameBoard *board = (GameBoard *)malloc(sizeof(GameBoard));
    board->width = width;
    board->height = height;
    board->board = (Block **)malloc(sizeof(Block *) * width);
    for (int i = 0; i < width; i++)
    {
        board->board[i] = (Block *)malloc(sizeof(Block) * height);
    }
    return board;
}

// ����C���ѽL���Ϊ����s
void destroyGameBoard(GameBoard *board)
{
    for (int i = 0; i < board->width; i++)
    {
        free(board->board[i]);
    }
    free(board->board);
    free(board);
}

// ��l�ƹC���ѽL
void initGameBoard(GameBoard *board)
{
    srand(time(NULL));
    for (int y = 0; y < board->height; y++)
    {
        for (int x = 0; x < board->width; x++)
        {
            board->board[x][y].color = rand() % COLORS;
        }
    }
}

// �L�X�C���ѽL
void printGameBoard(GameBoard *board)
{
    for (int y = 0; y < board->height; y++)
    {
        for (int x = 0; x < board->width; x++)
        {
            if (board->board[x][y].color == -1)
            {
                printf("  "); // �w���������
            }
            else
            {
                printf("%d ", board->board[x][y].color);
            }
        }
        printf("\n");
    }
}

// �洫��J����Ӥ������m
void swapBlocks(Block *a, Block *b)
{
    Block temp = *a;
    *a = *b;
    *b = temp;
}

// �ˬd�C���ѽL���O�_���i�H���������
int checkMatches(GameBoard *board)
{
    int matches = 0;
    // �ˬd�C�@��O�_���ŦX�������󪺤���s�u
    for (int y = 0; y < board->height; y++)
    {
        int count = 1;
        for (int x = 1; x < board->width; x++)
        {
            if (board->board[x][y].color == board->board[x - 1][y].color)
            {
                count++;
                if (count >= MIN_MATCH)
                {
                    // �аO�n���������
                    for (int i = x - count + 1; i <= x; i++)
                    {
                        board->board[i][y].color = -1;
                    }
                    matches++;
                }
            }
            else
            {
                count = 1;
            }
        }
    }
    // �ˬd�C�@�C�O�_���ŦX�������󪺤���s�u
    for (int x = 0; x < board->width; x++)
    {
        int count = 1;
        for (int y = 1; y < board->height; y++)
        {
            if (board->board[x][y].color == board->board[x][y - 1].color)
            {
                count++;
                if (count >= MIN_MATCH)
                {
                    // �аO�n���������
                    for (int i = y - count + 1; i <= y; i++)
                    {
                        board->board[x][i].color = -1;
                    }
                    matches++;
                }
            }
            else
            {
                count = 1;
            }
        }
    }

    // ��������ö񺡪Ů�
    for (int x = 0; x < board->width; x++)
    {
        int fillIndex = board->height - 1;
        for (int y = board->height - 1; y >= 0; y--)
        {
            if (board->board[x][y].color != -1)
            {
                board->board[x][fillIndex--].color = board->board[x][y].color;
            }
        }
        for (; fillIndex >= 0; fillIndex--)
        {
            board->board[x][fillIndex].color = -1;
        }
    }

    return matches;
}

// �ˬd�C���O�_�����]�Y�ѽL���O�_���۾F���C��i�H�����^
int checkGameEnd(GameBoard *board)
{
    for (int x = 0; x < board->width; x++)
    {
        for (int y = 0; y < board->height; y++)
        {
            if ((x > 0 && board->board[x][y].color == board->board[x - 1][y].color) ||
                (x < board->width - 1 && board->board[x][y].color == board->board[x + 1][y].color) ||
                (y > 0 && board->board[x][y].color == board->board[x][y - 1].color) ||
                (y < board->height - 1 && board->board[x][y].color == board->board[x][y + 1].color))
            {
                return 0; // �C���٥�����
            }
        }
    }
    return 1; // �C������
}

int main()
{
    GameBoard *board = createGameBoard(BOARD_WIDTH, BOARD_HEIGHT);
    initGameBoard(board);
    printf("�w��Ө�����ֹC��!\n");
    printf("���ձN 3 �өΧ�h�ۦP�C�⪺�϶��s�b�@�_!\n");
    printf("��J (x, y) �y�ШӲ���, �Ϋ�q�����C��\n");
    printf("��l�ѽL:\n");
    printGameBoard(board);

    int moves = 0;

    // �i�沾�ʤ��
    while (1)
    {
        int x1, y1, x2, y2;
        printf("��%d������, ��J�y�� (x1 y1 x2 y2): ", moves + 1);
        char input[10];
        fgets(input, sizeof(input), stdin); // Ū�����a��J���y��
        if (input[0] == 'q')
        {
            printf("�C������!");
            break;
        }
        sscanf(input, "%d %d %d %d", &x1, &y1, &x2, &y2); // ��J���y�г]�����

        // �y���ˬd
        if (abs(x1 - x2) + abs(y1 - y2) != 1)
        {
            printf("Invalid move. Please enter again.\n");
            continue;
        }

        // �洫�y�ФW�����
        swapBlocks(&board->board[x1][y1], &board->board[x2][y2]);

        moves++;
        printf("���� %d:\n", moves);
        printGameBoard(board); // ��ܲ��ʫ᪺�y�Ъ��A

        int matches = checkMatches(board); // �ˬd�O�_���ŦX�������󪺤���s�u
        if (matches > 0)
        {
            printf("�����Ӽ�: %d\n", matches / 2); // �p�G���ŦX�������󪺤���s�u�A�h��ܤǰt�ƶq
            printGameBoard(board);                 // ��ܧ�s�᪺�C���ѽL���A
            matches = checkMatches(board);         // �A���ˬd�O�_�٦��ŦX�������󪺤���s�u
        }

        // �ˬd�C���O�_����
        if (checkGameEnd(board))
        {
            printf("�L�k�A��������A�C�������C\n");
            break;
        }
    }

    destroyGameBoard(board);
    return 0;
}
