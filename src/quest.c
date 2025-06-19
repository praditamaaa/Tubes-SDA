#include "quest.h"

addressQuest createQuest(int id, QuestType type, const char* desc, int target) {
    addressQuest newQuest = (addressQuest)malloc(sizeof(Tquest));
    if (!newQuest) return NULL;

    newQuest->id = id;
    newQuest->type = type;
    strcpy(newQuest->description, desc);
    newQuest->target = target;
    newQuest->progress = 0;
    newQuest->completed = false;
    newQuest->next = NULL;
    newQuest->prev = NULL;
    return newQuest;
}

void addQuest(addressQuest* head, addressQuest newQuest) {
    if (!*head) {
        *head = newQuest;
        return;
    }

    addressQuest tail = *head;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = newQuest;
    newQuest->prev = tail;
}

void removeQuest(addressQuest* head, int id) {
    addressQuest curr = *head;
    while (curr != NULL && curr->id != id) {
        curr = curr->next;
    }

    if (!curr) return;

    if (curr->prev) curr->prev->next = curr->next;
    if (curr->next) curr->next->prev = curr->prev;
    if (curr == *head) *head = curr->next;

    free(curr);
}

void showAllQuests(addressQuest head) {
    int i = 1;
    printf("================== QUEST LIST ==================\n");
    while (head) {
        printf("%d. %s [%d/%d] - %s\n", i++, head->description, head->progress, head->target, head->completed ? "Completed" : "In Progress");
        head = head->next;
    }
    if (i == 1) printf("No active quests yet.\n");
    printf("===============================================\n");
}

bool questAlreadyExists(addressQuest head, int questId) {
    while (head) {
        if (head->id == questId) return true;
        head = head->next;
    }
    return false;
}

void assignRandomQuest(addressUser user) {
    const int TOTAL_QUESTS = 10;
    const char* descriptions[] = {
        "Reach Level 5",
        "Kill 10 Enemies",
        "Kill 5 Slimes",
        "Reach 500 Score",
        "Escape 3 Times",
        "Reach 50 Attack",
        "Reach 100 HP",
        "Reach 30 Defense",
        "Reach 200 Gold",
        "Complete 5 Quests"
    };
    int targets[] = {5, 10, 5, 500, 3, 50, 100, 30, 200, 5};
    QuestType types[] = {
        QUEST_REACH_LEVEL,
        QUEST_KILL_ENEMY_TOTAL,
        QUEST_KILL_ENEMY_TYPE,
        QUEST_COLLECT_SCORE,
        QUEST_ESCAPE_BATTLE,
        QUEST_REACH_ATTACK,
        QUEST_REACH_HP,
        QUEST_REACH_DEF,
        QUEST_REACH_GOLD,
        QUEST_TOTAL_QUEST_COMPLETED
    };

    int i, available[TOTAL_QUESTS];
    int count = 0;
    for (i = 0; i < TOTAL_QUESTS; i++) {
        if (!questAlreadyExists(user->questList, i)) {
            available[count++] = i;
        }
    }

    if (count == 0) {
        printf("All quests are owned.\n");
        return;
    }

    int randomIdx = available[rand() % count];
    addressQuest newQuest = createQuest(randomIdx, types[randomIdx], descriptions[randomIdx], targets[randomIdx]);
    addQuest(&user->questList, newQuest);
    printf("New quest accepted: %s\n", descriptions[randomIdx]);
}

void updateQuests(addressQuest head, addressChar k, RunTimeStats* stats) {
    while (head) {
        if (!head->completed) {
            switch (head->type) {
                case QUEST_REACH_LEVEL:
                    head->progress = k->Lvl;
                    break;
                case QUEST_COLLECT_SCORE:
                    head->progress = k->Exp;
                    break;
                case QUEST_REACH_ATTACK:
                    head->progress = k->Att;
                    break;
                case QUEST_REACH_DEF:
                    head->progress = k->Def;
                    break;
                case QUEST_REACH_HP:
                    head->progress = k->Hp;
                    break;
                case QUEST_REACH_GOLD:
                    head->progress = k->Gold;
                    break;
                case QUEST_KILL_ENEMY_TOTAL:
                    head->progress = getTotalKill(stats);
                    break;
                case QUEST_KILL_ENEMY_TYPE:
                    if (head->target >= 0 && head->target < MAX_ENEMY_TYPE) {
                        head->progress = stats->killCountPerType[head->target];
                    }
                    break;
                case QUEST_ESCAPE_BATTLE:
                    head->progress = stats->battlesEscaped;
                    break;
                case QUEST_TOTAL_QUEST_COMPLETED:
                    head->progress = stats->completedQuests;
                    break;
                default:
                    break;
            }

            if (head->progress >= head->target) {
                head->progress = head->target;
                head->completed = true;
                stats->completedQuests++;
                printf("\n>>> Quest Completed: %s!\n", head->description);
            }
        }
        head = head->next;
    }
}

