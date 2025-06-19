#include "quest.h"
#include "User.h"

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
    
    // Tiap quest di random rewardnya dgn range tertentu
    switch (type) {
        case QUEST_REACH_LEVEL:
            newQuest->rewardExp = rand() % 51 + 50;     
            newQuest->rewardGold = rand() % 51 + 50;    
            break;
        case QUEST_KILL_ENEMY_TOTAL:
            newQuest->rewardExp = rand() % 101 + 100;   
            newQuest->rewardGold = rand() % 101 + 100;  
            break;
        case QUEST_KILL_ENEMY_TYPE:
            newQuest->rewardExp = rand() % 51 + 75;
            newQuest->rewardGold = rand() % 51 + 75;
            break;
        case QUEST_COLLECT_SCORE:
            newQuest->rewardGold = rand() % 51 + 100;
            break;
        case QUEST_ESCAPE_BATTLE:
            newQuest->rewardGold = rand() % 21 + 30;
            break;
        case QUEST_REACH_ATTACK:
            newQuest->rewardAtt = 1;
            newQuest->rewardGold = rand() % 21 + 50;
            break;
        case QUEST_REACH_DEF:
            newQuest->rewardDef = 1;
            newQuest->rewardGold = rand() % 21 + 50;
            break;
        case QUEST_REACH_HP:
            newQuest->rewardExp = rand() % 41 + 60;
            break;
        case QUEST_REACH_GOLD:
            newQuest->rewardExp = rand() % 41 + 60;
            break;
        case QUEST_TOTAL_QUEST_COMPLETED:
            newQuest->rewardGold = 100;
            newQuest->rewardExp = 100;
            break;
        default:
            newQuest->rewardGold = 10;
            break;
    }
    
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
	printf("Reward: +%d Gold, +%d Exp, +%d Att, +%d Def\n", newQuest->rewardGold, newQuest->rewardExp, newQuest->rewardAtt, newQuest->rewardDef);
}

void updateQuests(addressQuest head, addressChar k, runTimeStats* stats) {
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
                    head->progress = stats->totalBattlesEscape;
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

void giveQuestReward(addressChar k, RunTimeStats* stats, addressQuest q) {
    if (!q || !k || !stats) return;

    if (q->completed) {
        k->Gold += q->rewardGold;
        k->Exp += q->rewardExp;
        k->Att += q->rewardAtt;
        k->Def += q->rewardDef;

        printf("\n--- QUEST REWARD ---\n");
        if (q->rewardGold) printf("+%d Gold\n", q->rewardGold);
        if (q->rewardExp)  printf("+%d Exp\n", q->rewardExp);
        if (q->rewardAtt)  printf("+%d Attack\n", q->rewardAtt);
        if (q->rewardDef)  printf("+%d Defense\n", q->rewardDef);
        printf("--------------------\n");

        // quest dihapus Setelah reward diberikan
        removeQuest(&stats->user->questList, q->id);
    }
}

void claimQuestReward(addressUser user, int questId) {
    addressQuest q = user->questList;
    while (q && q->id != questId) {
        q = q->next;
    }

    if (!q) {
        printf("Quest not found.\n");
        return;
    }

    if (!q->completed) {
        printf("Quest not done.\n");
        return;
    }

    giveQuestReward(&user->character, q);
    removeQuest(&user->questList, q->id);
    user->stats.totalQuestCompleted++;
}

