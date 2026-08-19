#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "student.bin"
#define PASS_MARK 40
#define MAX 100

struct marks {
    int  phy;
    int  maths;
    int  cpro;
    int  edrg;
    int  fee;
    float per;
    int  t;
};

struct student {
    char name[50];
    char email[50];
    int  s_id;
    char ph_no[11];
    struct marks m;
};

int  create();
int  read_records();
int  update();
int  delete_record();
int  search();
int  sort_records();
int  dall();
void pass_fail();
//helping function
void print_header();
void print_divider(char c, int len);
int  id_exists(int id);
int  load_all(struct student *arr);
void save_all(struct student *arr, int count);

int main()
{
    int n;

    print_header();

menu:
    printf("\n");
    printf("  +---------------------------------------------------+\n");
    printf("  |                   MAIN MENU                       |\n");
    printf("  +---------------------------------------------------+\n");
    printf("  |                                                   |\n");
    printf("  |   [1]  Add Student Record                        |\n");
    printf("  |   [2]  View All Records                          |\n");
    printf("  |   [3]  Update Student Record                     |\n");
    printf("  |   [4]  Delete Student Record                     |\n");
    printf("  |   [5]  Search by Student ID                      |\n");
    printf("  |   [6]  Sort by Total Marks                       |\n");
    printf("  |   [7]  Pass / Fail Report                        |\n");
    printf("  |   [8]  Delete ALL Records                        |\n");
    printf("  |   [0]  Exit                                      |\n");
    printf("  |                                                   |\n");
    printf("  +---------------------------------------------------+\n");

    printf("\n  Enter your choice: ");
    if (scanf("%d", &n) != 1) { while (getchar() != '\n'); goto menu; }

    printf("\n");
    switch (n) {
        case 1:
            printf("  ========== ADD STUDENT RECORD ==========\n\n");
            create();
                 break;
        case 2:
            printf("  ========== ALL STUDENT RECORDS ==========\n\n");
            read_records();
             break;
        case 3:
            printf("  ========== UPDATE STUDENT RECORD ==========\n\n");
            update();
             break;
        case 4:
            printf("  ========== DELETE STUDENT RECORD ==========\n\n");
            delete_record();
            break;
        case 5:
            printf("  ========== SEARCH STUDENT RECORD ==========\n\n");
            search();
               break;
        case 6:
            printf("  ========== SORTED RECORDS (by Total) ==========\n\n");
            sort_records();
            break;
        case 7:
            printf("  ========== PASS / FAIL REPORT ==========\n\n");
            pass_fail();
            break;
        case 8:
            printf("  ========== DELETE ALL RECORDS ==========\n\n");
            dall();
             break;
        case 0:
            printf("\n  ***************************************************\n");
            printf("  *              Goodbye! Exiting program...         *\n");
            printf("  ***************************************************\n\n");
            return 0;
        default:
            printf("  [!!] Invalid choice. Please try again.\n");
    }

    goto menu;
}
void print_header()
{
    printf("\n");
    printf("  ***************************************************\n");
    printf("  *                                                 *\n");
    printf("  *         STUDENT MANAGEMENT SYSTEM              *\n");
    printf("  *           Binary File Edition v2.0             *\n");
    printf("  *                                                 *\n");
    printf("  ***************************************************\n");
    printf("\n");
}
int id_exists(int id)
{
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) return 0;

    struct student tmp;
    while (fread(&tmp, sizeof(struct student), 1, fp) == 1) {
        if (tmp.s_id == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
int load_all(struct student *arr)
{
    FILE *fp = fopen(FILENAME, "rb");
    if (fp==NULL)
    return 0;

    int count = 0;
    while (fread(&arr[count], sizeof(struct student), 1, fp) == 1)
        count++;

    fclose(fp);
    return count;
}
void save_all(struct student *arr, int count)
{
    FILE *fp = fopen(FILENAME, "wb");
    if (!fp) {
        printf("  [ERROR] Cannot open file for writing.\n");
         return;
        }

    fwrite(arr, sizeof(struct student), count, fp);
    fclose(fp);
}
int create()
{
    int num, i;
    printf("  How many students to add: ");
    scanf("%d", &num);

    struct student s[MAX];
    int added = 0;

    for (i = 0; i < num; i++) {
        printf("\n  +--------- Student %d ---------+\n", i + 1);
        do {
            printf("  | Student ID       : ");
            scanf("%d", &s[added].s_id);
            if (id_exists(s[added].s_id)) {
                printf("  [X] ID %d already exists! Enter a different ID.\n", s[added].s_id);
            } else {
                int dup_in_batch = 0;
                for (int k = 0; k < added; k++) {
                    if (s[k].s_id == s[added].s_id) { dup_in_batch = 1; break; }
                }
                if (dup_in_batch) {
                    printf("  [X] ID %d already used in this batch!\n", s[added].s_id);
                } else break;
            }
        } while (1);

        printf("  | Name             : ");
         scanf("%49s",  s[added].name);
        printf("  | Email            : ");
         scanf("%49s",  s[added].email);
        printf("  | Phone Number     : ");
         scanf("%10s",  s[added].ph_no);

        printf("\n  --- Marks (out of 100 each) ---\n");
        printf("  | Physics          : ");
        scanf("%d", &s[added].m.phy);
        printf("  | Maths            : ");
        scanf("%d", &s[added].m.maths);
        printf("  | C Programming    : ");
        scanf("%d", &s[added].m.cpro);
        printf("  | Electrical & Elec: ");
        scanf("%d", &s[added].m.fee);
        printf("  | Engineering Draw : ");
        scanf("%d", &s[added].m.edrg);

        int sum = s[added].m.phy + s[added].m.maths + s[added].m.cpro
                + s[added].m.fee + s[added].m.edrg;
        s[added].m.t   = sum;
        s[added].m.per = sum / 5.0f;

        added++;
    }
    FILE *fp = fopen(FILENAME, "ab");
    if (!fp) { printf("  [ERROR] Cannot open file.\n"); return -1; }

    fwrite(s, sizeof(struct student), added, fp);
    fclose(fp);

    printf("\n  [OK] %d student record(s) saved successfully.\n\n", added);
    return 0;
}
int read_records()
{
    struct student s[MAX];
    int count = load_all(s);

    if (count == 0) {
        printf("  No records found.\n\n");
        return 0;
    }

    printf("  +------+-----------------+----------------------+-------------+--------+---------+\n");
    printf("  | ID   | Name            | Email                | Phone       | Total  | Percent |\n");
    printf("  +------+-----------------+----------------------+-------------+--------+---------+\n");

    for (int i = 0; i < count; i++) {
        printf("  | %-4d | %-15s | %-20s | %-11s | %-6d | %-7.2f |\n",
               s[i].s_id, s[i].name, s[i].email,
               s[i].ph_no, s[i].m.t, s[i].m.per);
    }

    printf("  +------+-----------------+----------------------+-------------+--------+---------+\n");
    printf("  Total records: %d\n\n", count);
    return 0;
}

int update()
{
    struct student s[MAX];
    int count = load_all(s);

    if (count == 0) {
        printf("  No records to update.\n\n");
        return 0;
    }

    int id, found = -1;
    printf("  Enter Student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (s[i].s_id == id) { found = i; break; }
    }

    if (found == -1) {
        printf("  [X] Student ID %d not found.\n\n", id);
        return -1;
    }

    printf("\n  Current record found. Enter new details (0 to skip fields).\n\n");
    printf("  Current Name: %s\n", s[found].name);
    int new_id;
    printf("  New Student ID (0 = keep %d): ", s[found].s_id);
    scanf("%d", &new_id);
    if (new_id != 0 && new_id != s[found].s_id) {
        if (id_exists(new_id)) {
            printf("  [X] ID %d already exists. ID not changed.\n", new_id);
        } else {
            s[found].s_id = new_id;
        }
    }

    char buf[50];
    printf("  New Name (0 to skip): "); scanf("%49s", buf);
    if (strcmp(buf, "0") != 0 && strlen(buf) > 0) strncpy(s[found].name, buf, 49);

    printf("  New Email (0 to skip): "); scanf("%49s", buf);
    if (strcmp(buf, "0") != 0 && strlen(buf) > 0) strncpy(s[found].email, buf, 49);

    printf("  New Phone (0 to skip): "); scanf("%10s", buf);
    if (strcmp(buf, "0") != 0 && strlen(buf) > 0) strncpy(s[found].ph_no, buf, 10);

    printf("\n  Update marks? (1=Yes / 0=No): ");
    int upd_marks; scanf("%d", &upd_marks);
    if (upd_marks == 1) {
        printf("  Physics             : "); scanf("%d", &s[found].m.phy);
        printf("  Maths               : "); scanf("%d", &s[found].m.maths);
        printf("  C Programming       : "); scanf("%d", &s[found].m.cpro);
        printf("  Electrical & Elec.  : "); scanf("%d", &s[found].m.fee);
        printf("  Engineering Drawing : "); scanf("%d", &s[found].m.edrg);

        int sum = s[found].m.phy + s[found].m.maths + s[found].m.cpro
                + s[found].m.fee + s[found].m.edrg;
        s[found].m.t   = sum;
        s[found].m.per = sum / 5.0f;
    }

    save_all(s, count);
    printf("\n  [OK] Record updated successfully.\n\n");
    return 0;
}

/* ================================================================
 *  DELETE  –  Remove one record by s_id, rewrite file
 * ================================================================ */
int delete_record()
{
    struct student s[MAX];
    int count = load_all(s);

    if (count == 0) {
        printf("  No records found.\n\n");
        return 0;
    }

    int id;
    printf("  Enter Student ID to delete: ");
    scanf("%d", &id);

    struct student temp[MAX];
    int new_count = 0, found = 0;

    for (int i = 0; i < count; i++) {
        if (s[i].s_id == id) {
            found = 1;
            printf("  [OK] Record of ID %d deleted.\n", id);
        } else {
            temp[new_count++] = s[i];
        }
    }

    if (!found) {
        printf("  [X] Student ID %d not found.\n\n", id);
        return -1;
    }

    save_all(temp, new_count);
    printf("\n");
    return 0;
}

/* ================================================================
 *  SEARCH  –  Find and display a record by s_id
 * ================================================================ */
int search()
{
    int id;
    printf("  Enter Student ID to search: ");
    scanf("%d", &id);

    struct student s[MAX];
    int count = load_all(s);

    for (int i = 0; i < count; i++) {
        if (s[i].s_id == id) {
            printf("\n");
            printf("  +---------------------------------------+\n");
            printf("  |         STUDENT DETAILS               |\n");
            printf("  +---------------------------------------+\n");
            printf("  | ID          : %-17d |\n", s[i].s_id);
            printf("  | Name        : %-17s |\n", s[i].name);
            printf("  | Email       : %-17s |\n", s[i].email);
            printf("  | Phone       : %-17s |\n", s[i].ph_no);
            printf("  +---------------------------------------+\n");
            printf("  | Physics     : %-17d |\n", s[i].m.phy);
            printf("  | Maths       : %-17d |\n", s[i].m.maths);
            printf("  | C Prog.     : %-17d |\n", s[i].m.cpro);
            printf("  | Elec.       : %-17d |\n", s[i].m.fee);
            printf("  | Eng. Draw   : %-17d |\n", s[i].m.edrg);
            printf("  +---------------------------------------+\n");
            printf("  | Total       : %-17d |\n", s[i].m.t);
            printf("  | Percentage  : %-17.2f |\n", s[i].m.per);
            printf("  +---------------------------------------+\n\n");
            return 0;
        }
    }

    printf("  [X] Student ID %d not found.\n\n", id);
    return -1;
}

/* ================================================================
 *  SORT  –  Bubble sort by total marks (descending), display table
 * ================================================================ */
int sort_records()
{
    struct student s[MAX];
    int count = load_all(s);

    if (count == 0) {
        printf("  No records found.\n\n");
        return 0;
    }

    /* Bubble sort (descending by total) */
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (s[j].m.t < s[j + 1].m.t) {
                struct student tmp = s[j];
                s[j]     = s[j + 1];
                s[j + 1] = tmp;
            }
        }
    }

    printf("  Sorted by Total Marks (Highest -> Lowest)\n\n");
    printf("  +------+-----------------+--------+---------+--------+\n");
    printf("  | Rank | Name            | Total  | Percent | Status |\n");
    printf("  +------+-----------------+--------+---------+--------+\n");

    for (int i = 0; i < count; i++) {
        int pass = (s[i].m.phy >= PASS_MARK && s[i].m.maths >= PASS_MARK &&
                    s[i].m.cpro >= PASS_MARK && s[i].m.fee >= PASS_MARK &&
                    s[i].m.edrg >= PASS_MARK);
        const char *status = pass ? "PASS" : "FAIL";

        printf("  | %-4d | %-15s | %-6d | %-7.2f | %-6s |\n",
               i + 1, s[i].name, s[i].m.t, s[i].m.per, status);
    }

    printf("  +------+-----------------+--------+---------+--------+\n\n");
    return 0;
}

/* ================================================================
 *  PASS_FAIL  –  NEW FUNCTION
 *  A student PASSES if ALL subjects >= PASS_MARK (40).
 *  Displays two separate tables: passing students and failing ones.
 * ================================================================ */
void pass_fail()
{
    struct student s[MAX];
    int count = load_all(s);

    if (count == 0) {
        printf("  No records found.\n\n");
        return;
    }

    struct student pass_list[MAX], fail_list[MAX];
    int p_count = 0, f_count = 0;

    for (int i = 0; i < count; i++) {
        int passed = (s[i].m.phy   >= PASS_MARK &&
                      s[i].m.maths >= PASS_MARK &&
                      s[i].m.cpro  >= PASS_MARK &&
                      s[i].m.fee   >= PASS_MARK &&
                      s[i].m.edrg  >= PASS_MARK);
        if (passed)
            pass_list[p_count++] = s[i];
        else
            fail_list[f_count++] = s[i];
    }

    printf("  [PASSING STUDENTS]  (%d / %d)\n", p_count, count);
    if (p_count == 0) {
        printf("  None\n\n");
    } else {
        printf("  +------+-----------------+--------+---------+\n");
        printf("  | ID   | Name            | Total  | Percent |\n");
        printf("  +------+-----------------+--------+---------+\n");
        for (int i = 0; i < p_count; i++)
            printf("  | %-4d | %-15s | %-6d | %-7.2f |\n",
                   pass_list[i].s_id, pass_list[i].name,
                   pass_list[i].m.t,  pass_list[i].m.per);
        printf("  +------+-----------------+--------+---------+\n\n");
    }
    printf("  [FAILING STUDENTS]  (%d / %d)\n", f_count, count);
    if (f_count == 0) {
        printf("  None\n\n");
    } else {
        printf("  +------+-----------------+--------+---------+-----------------------------+\n");
        printf("  | ID   | Name            | Total  | Percent | Failed Subject(s)            |\n");
        printf("  +------+-----------------+--------+---------+-----------------------------+\n");
        for (int i = 0; i < f_count; i++) {
            char subjects[100] = "";
            if (fail_list[i].m.phy   < PASS_MARK) strcat(subjects, "Phy ");
            if (fail_list[i].m.maths < PASS_MARK) strcat(subjects, "Math ");
            if (fail_list[i].m.cpro  < PASS_MARK) strcat(subjects, "CPro ");
            if (fail_list[i].m.fee   < PASS_MARK) strcat(subjects, "Elec ");
            if (fail_list[i].m.edrg  < PASS_MARK) strcat(subjects, "Draw ");

            printf("  | %-4d | %-15s | %-6d | %-7.2f | %-27s |\n",
                   fail_list[i].s_id, fail_list[i].name,
                   fail_list[i].m.t,  fail_list[i].m.per, subjects);
        }
        printf("  +------+-----------------+--------+---------+-----------------------------+\n\n");
    }
}
int dall()
{
    int d;
    printf("  Press 1 to delete ALL records (irreversible): ");
    scanf("%d", &d);

    if (d != 1) return 0;

    char pass[20];
    printf("  Enter password: ");
    scanf("%19s", pass);

    if (strcmp(pass, "*delete*") == 0) {
        remove(FILENAME);
        printf("  [OK] All records deleted.\n\n");
    } else {
        printf("  [X] Authentication failed!\n\n");
    }
    return 0;
}
