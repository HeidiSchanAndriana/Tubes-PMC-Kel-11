#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATIENTS 1000
#define MAX_RECORDS 1000
#define MAX_ACTIVITIES 100

typedef struct {
    int id;
    char full_name[100];
    char address[150];
    char city[50];
    char birth_place[50];
    char birth_date[30];
    int age;
    char bpjs_number[20];
    char patient_id[20];
} Patient;

typedef struct {
    int id;
    char visit_date[20];
    char patient_id[20];
    char diagnosis[100];
    char treatment[100];
    char follow_up_date[20];
    double cost;
} MedicalRecord;

Patient patients[MAX_PATIENTS];
MedicalRecord records[MAX_RECORDS];
int patient_count = 0;
int record_count = 0;

char *strptime(const char *buf, const char *format, struct tm *tm) {
    return strptime(buf, format, tm);
}

void read_patients_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s for reading\n", filename);
        return;
    }

    char line[512];
    fgets(line, sizeof(line), file); // Skip header line

    while (fgets(line, sizeof(line), file)) {
        Patient p;
        char *token = strtok(line, ";");
        p.id = atoi(token);

        token = strtok(NULL, ";");
        strcpy(p.full_name, token);

        token = strtok(NULL, ";");
        strcpy(p.address, token);

        token = strtok(NULL, ";");
        strcpy(p.city, token);

        token = strtok(NULL, ";");
        strcpy(p.birth_place, token);

        token = strtok(NULL, ";");
        strcpy(p.birth_date, token);

        token = strtok(NULL, ";");
        p.age = atoi(token);

        token = strtok(NULL, ";");
        strcpy(p.bpjs_number, token);

        token = strtok(NULL, ";");
        strcpy(p.patient_id, token);

        patients[patient_count++] = p;
    }

    fclose(file);
}

void read_medical_records_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s for reading\n", filename);
        return;
    }

    char line[512];
    fgets(line, sizeof(line), file); // Skip header line

    while (fgets(line, sizeof(line), file)) {
        MedicalRecord r;
        char *token = strtok(line, ";");
        r.id = atoi(token);

        token = strtok(NULL, ";");
        strcpy(r.visit_date, token);

        token = strtok(NULL, ";");
        strcpy(r.patient_id, token);

        token = strtok(NULL, ";");
        strcpy(r.diagnosis, token);

        token = strtok(NULL, ";");
        strcpy(r.treatment, token);

        token = strtok(NULL, ";");
        strcpy(r.follow_up_date, token);

        token = strtok(NULL, ";");
        r.cost = atof(token);

        records[record_count++] = r;
    }

    fclose(file);
}

void add_patient() {
    if (patient_count >= MAX_PATIENTS) {
        printf("Patient list is full!\n");
        return;
    }

    Patient p;
    printf("Enter ID: ");
    scanf("%d", &p.id);
    printf("Enter Full Name: ");
    scanf(" %[^\n]", p.full_name);
    printf("Enter Address: ");
    scanf(" %[^\n]", p.address);
    printf("Enter City: ");
    scanf(" %[^\n]", p.city);
    printf("Enter Birth Place: ");
    scanf(" %[^\n]", p.birth_place);
    printf("Enter Birth Date (DD MMM YYYY): ");
    scanf(" %[^\n]", p.birth_date);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter BPJS Number: ");
    scanf(" %[^\n]", p.bpjs_number);
    printf("Enter Patient ID: ");
    scanf(" %[^\n]", p.patient_id);

    patients[patient_count++] = p;

    FILE *file = fopen("data1.csv", "a");
    if (!file) {
        printf("Could not open file data1.csv for writing\n");
        return;
    }

    fprintf(file, "%d;%s;%s;%s;%s;%s;%d;%s;%s\n", p.id, p.full_name, p.address, p.city, p.birth_place, p.birth_date, p.age, p.bpjs_number, p.patient_id);
    fclose(file);

    printf("Patient added successfully!\n");
}

void update_patient() {
    char patient_id[20];
    printf("Enter Patient ID to update: ");
    scanf(" %[^\n]", patient_id);

    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].patient_id, patient_id) == 1) {
            printf("Enter new Full Name: ");
            scanf(" %[^\n]", patients[i].full_name);
            printf("Enter new Address: ");
            scanf(" %[^\n]", patients[i].address);
            printf("Enter new City: ");
            scanf(" %[^\n]", patients[i].city);
            printf("Enter new Birth Place: ");
            scanf(" %[^\n]", patients[i].birth_place);
            printf("Enter new Birth Date (DD MMM YYYY): ");
            scanf(" %[^\n]", patients[i].birth_date);
            printf("Enter new Age: ");
            scanf("%d", &patients[i].age);
            printf("Enter new BPJS Number: ");
            scanf(" %[^\n]", patients[i].bpjs_number);

            // Update CSV file
            FILE *file = fopen("data1.csv", "w");
            if (!file) {
                printf("Could not open file data1.csv for writing\n");
                return;
            }

            fprintf(file, "ID;Full Name;Address;City;Birth Place;Birth Date;Age;BPJS Number;Patient ID\n");
            for (int j = 0; j < patient_count; j++) {
                fprintf(file, "%d;%s;%s;%s;%s;%s;%d;%s;%s\n", patients[j].id, patients[j].full_name, patients[j].address, patients[j].city, patients[j].birth_place, patients[j].birth_date, patients[j].age, patients[j].bpjs_number, patients[j].patient_id);
            }
            fclose(file);

            printf("Patient updated successfully!\n");
            return;
        }
    }
    printf("Patient not found.\n");
}

void delete_patient() {
    char patient_id[20];
    printf("Enter Patient ID to delete: ");
    scanf(" %[^\n]", patient_id);

    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].patient_id, patient_id) == 1) {
            for (int j = i; j < patient_count - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patient_count--;

            // Update CSV file
            FILE *file = fopen("data1.csv", "w");
            if (!file) {
                printf("Could not open file data1.csv for writing\n");
                return;
            }

            fprintf(file, "ID;Full Name;Address;City;Birth Place;Birth Date;Age;BPJS Number;Patient ID\n");
            for (int j = 0; j < patient_count; j++) {
                fprintf(file, "%d;%s;%s;%s;%s;%s;%d;%s;%s\n", patients[j].id, patients[j].full_name, patients[j].address, patients[j].city, patients[j].birth_place, patients[j].birth_date, patients[j].age, patients[j].bpjs_number, patients[j].patient_id);
            }
            fclose(file);

            printf("Patient deleted successfully!\n");
            return;
        }
    }
    printf("Patient not found.\n");
}

void add_medical_record() {
    if (record_count >= MAX_RECORDS) {
        printf("Medical record list is full!\n");
        return;
    }

    MedicalRecord r;
    printf("Enter ID: ");
    scanf("%d", &r.id);
    printf("Enter Visit Date (DD MMM YYYY): ");
    scanf(" %[^\n]", r.visit_date);
    printf("Enter Patient ID: ");
    scanf(" %[^\n]", r.patient_id);
    printf("Enter Diagnosis: ");
    scanf(" %[^\n]", r.diagnosis);
    printf("Enter Treatment: ");
    scanf(" %[^\n]", r.treatment);
    printf("Enter Follow-Up Date (DD MMM YYYY): ");
    scanf(" %[^\n]", r.follow_up_date);
    printf("Enter Cost: ");
    scanf("%lf", &r.cost);

    records[record_count++] = r;

    FILE *file = fopen("data2.csv", "a");
    if (!file) {
        printf("Could not open file data2.csv for writing\n");
        return;
    }

    fprintf(file, "%d;%s;%s;%s;%s;%s;%.2f\n", r.id, r.visit_date, r.patient_id, r.diagnosis, r.treatment, r.follow_up_date, r.cost);
    fclose(file);

    printf("Medical record added successfully!\n");
}

void update_medical_record() {
    int record_id;
    printf("Enter Record ID to update: ");
    scanf("%d", &record_id);

    for (int i = 0; i < record_count; i++) {
        if (records[i].id == record_id) {
            printf("Enter new Visit Date (DD MMM YYYY): ");
            scanf(" %[^\n]", records[i].visit_date);
            printf("Enter new Patient ID: ");
            scanf(" %[^\n]", records[i].patient_id);
            printf("Enter new Diagnosis: ");
            scanf(" %[^\n]", records[i].diagnosis);
            printf("Enter new Treatment: ");
            scanf(" %[^\n]", records[i].treatment);
            printf("Enter new Follow-Up Date (DD MMM YYYY): ");
            scanf(" %[^\n]", records[i].follow_up_date);
            printf("Enter new Cost: ");
            scanf("%lf", &records[i].cost);

            // Update CSV file
            FILE *file = fopen("data2.csv", "w");
            if (!file) {
                printf("Could not open file data2.csv for writing\n");
                return;
            }

            fprintf(file, "ID;Visit Date;Patient ID;Diagnosis;Treatment;Follow-Up Date;Cost\n");
            for (int j = 0; j < record_count; j++) {
                fprintf(file, "%d;%s;%s;%s;%s;%s;%.2f\n", records[j].id, records[j].visit_date, records[j].patient_id, records[j].diagnosis, records[j].treatment, records[j].follow_up_date, records[j].cost);
            }
            fclose(file);

            printf("Medical record updated successfully!\n");
            return;
        }
    }
    printf("Record not found.\n");
}

void delete_medical_record() {
    int record_id;
    printf("Enter Record ID to delete: ");
    scanf("%d", &record_id);

    for (int i = 0; i < record_count; i++) {
        if (records[i].id == record_id) {
            for (int j = i; j < record_count - 1; j++) {
                records[j] = records[j + 1];
            }
            record_count--;

            // Update CSV file
            FILE *file = fopen("data2.csv", "w");
            if (!file) {
                printf("Could not open file data2.csv for writing\n");
                return;
            }

            fprintf(file, "ID;Visit Date;Patient ID;Diagnosis;Treatment;Follow-Up Date;Cost\n");
            for (int j = 0; j < record_count; j++) {
                fprintf(file, "%d;%s;%s;%s;%s;%s;%.2f\n", records[j].id, records[j].visit_date, records[j].patient_id, records[j].diagnosis, records[j].treatment, records[j].follow_up_date, records[j].cost);
            }
            fclose(file);

            printf("Medical record deleted successfully!\n");
            return;
        }
    }
    printf("Record not found.\n");
}

void search_patient() {
    char patient_id[20];
    printf("Enter Patient ID to search: ");
    scanf(" %[^\n]", patient_id);

    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].patient_id, patient_id) == 1) {
            printf("Patient found:\n");
            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].full_name);
            printf("Address: %s\n", patients[i].address);
            printf("City: %s\n", patients[i].city);
            printf("Birth Place: %s\n", patients[i].birth_place);
            printf("Birth Date: %s\n", patients[i].birth_date);
            printf("Age: %d\n", patients[i].age);
            printf("BPJS Number: %s\n", patients[i].bpjs_number);
            printf("Patient ID: %s\n", patients[i].patient_id);
            return;
        }
    }
    printf("Patient not found.\n");
}

void display_patient_info() {
    char patient_id[20];
    printf("Enter Patient ID to display information: ");
    scanf(" %[^\n]", patient_id);

    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].patient_id, patient_id) == 1) {
            printf("Patient Information:\n");
            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].full_name);
            printf("Address: %s\n", patients[i].address);
            printf("City: %s\n", patients[i].city);
            printf("Birth Place: %s\n", patients[i].birth_place);
            printf("Birth Date: %s\n", patients[i].birth_date);
            printf("Age: %d\n", patients[i].age);
            printf("BPJS Number: %s\n", patients[i].bpjs_number);
            printf("Patient ID: %s\n", patients[i].patient_id);

            printf("Medical Records:\n");
            for (int j = 0; j < record_count; j++) {
                if (strcmp(records[j].patient_id, patient_id) == 0) {
                    printf("Visit Date: %s\n", records[j].visit_date);
                    printf("Diagnosis: %s\n", records[j].diagnosis);
                    printf("Treatment: %s\n", records[j].treatment);
                    printf("Follow-Up Date: %s\n", records[j].follow_up_date);
                    printf("Cost: %.2lf\n", records[j].cost);
                }
            }
            return;
        }
    }
    printf("Patient not found.\n");
}

void generate_income_report() {
    int year;
    printf("Enter year for income report: ");
    scanf("%d", &year);

    double monthly_income[12] = {0};
    double yearly_income = 0;

    for (int i = 0; i < record_count; i++) {
        struct tm visit_date = {0};
        strptime(records[i].visit_date, "%d %b %Y", &visit_date);
        if (visit_date.tm_year + 1900 == year) {
            monthly_income[visit_date.tm_mon] += records[i].cost;
            yearly_income += records[i].cost;
        }
    }

    printf("Monthly Income Report for %d:\n", year);
    for (int i = 0; i < 12; i++) {
        printf("Month %d: %.2f\n", i + 1, monthly_income[i]);
    }
    printf("Total Yearly Income: %.2f\n", yearly_income);
}

void generate_patient_statistics() {
    int year;
    printf("Enter year for patient statistics: ");
    scanf("%d", &year);

    int monthly_patient_count[12] = {0};
    int total_patient_count = 0;

    char diagnoses[MAX_RECORDS][100];
    int diagnosis_count[MAX_RECORDS] = {0};
    int diagnosis_index = 0;

    for (int i = 0; i < record_count; i++) {
        struct tm visit_date = {0};
        strptime(records[i].visit_date, "%d %b %Y", &visit_date);
        if (visit_date.tm_year + 1900 == year) {
            monthly_patient_count[visit_date.tm_mon]++;
            total_patient_count++;

            int found = 0;
            for (int j = 0; j < diagnosis_index; j++) {
                if (strcmp(diagnoses[j], records[i].diagnosis) == 0) {
                    diagnosis_count[j]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(diagnoses[diagnosis_index], records[i].diagnosis);
                diagnosis_count[diagnosis_index++] = 1;
            }
        }
    }

    printf("Monthly Patient Count for %d:\n", year);
    for (int i = 0; i < 12; i++) {
        printf("Month %d: %d\n", i + 1, monthly_patient_count[i]);
    }
    printf("Total Yearly Patient Count: %d\n", total_patient_count);

    printf("Diagnosis Statistics:\n");
    for (int i = 0; i < diagnosis_index; i++) {
        printf("%s: %d\n", diagnoses[i], diagnosis_count[i]);
    }
}

void check_follow_up() {
    time_t now;
    time(&now);
    struct tm *current_time = localtime(&now);

    printf("Patients who need follow-up:\n");
    for (int i = 0; i < record_count; i++) {
        struct tm follow_up_date = {0};
        strptime(records[i].follow_up_date, "%d %b %Y", &follow_up_date);
        if (difftime(mktime(&follow_up_date), now) <= 0) {
            for (int j = 0; j < patient_count; j++) {
                if (strcmp(patients[j].patient_id, records[i].patient_id) == 0) {
                    printf("Patient ID: %s, Name: %s, Follow-Up Date: %s\n", patients[j].patient_id, patients[j].full_name, records[i].follow_up_date);
                    break;
                }
            }
        }
    }
}

int main() {
    read_patients_csv("data1.csv");  // Membaca file CSV pertama
    read_medical_records_csv("data2.csv");  // Membaca file CSV kedua

    int choice;
    while (1) {
        printf("\nClinic X Patient Management System\n");
        printf("1. Add Patient\n");
        printf("2. Update Patient\n");
        printf("3. Delete Patient\n");
        printf("4. Search Patient\n");
        printf("5. Add Medical Record\n");
        printf("6. Update Medical Record\n");
        printf("7. Delete Medical Record\n");
        printf("8. Display Patient Information\n");
        printf("9. Generate Income Report\n");
        printf("10. Generate Patient Statistics\n");
        printf("11. Check Follow-Up\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_patient();
                break;
            case 2:
                update_patient();
                break;
            case 3:
                delete_patient();
                break;
            case 4:
                search_patient();
                break;
            case 5:
                add_medical_record();
                break;
            case 6:
                update_medical_record();
                break;
            case 7:
                delete_medical_record();
                break;
            case 8:
                display_patient_info();
                break;
            case 9:
                generate_income_report();
                break;
            case 10:
                generate_patient_statistics();
                break;
            case 11:
                check_follow_up();
                break;
            case 0:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

