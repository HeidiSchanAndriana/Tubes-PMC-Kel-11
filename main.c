#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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

// Fungsi untuk mengonversi nama bulan dari bahasa Indonesia ke bahasa Inggris
const char* convert_month(const char* month) {
    if (strcasecmp(month, "Januari") == 0) return "Jan";
    if (strcasecmp(month, "Februari") == 0) return "Feb";
    if (strcasecmp(month, "Maret") == 0) return "Mar";
    if (strcasecmp(month, "April") == 0) return "Apr";
    if (strcasecmp(month, "Mei") == 0) return "Mei";
    if (strcasecmp(month, "Juni") == 0) return "Jun";
    if (strcasecmp(month, "Juli") == 0) return "Jul";
    if (strcasecmp(month, "Agustus") == 0) return "Agu";
    if (strcasecmp(month, "September") == 0) return "Sep";
    if (strcasecmp(month, "Oktober") == 0) return "Okt";
    if (strcasecmp(month, "November") == 0) return "Nov";
    if (strcasecmp(month, "Desember") == 0) return "Des";
    return month;
}

// Fungsi untuk mengonversi nama bulan ke angka bulan (0-11)
int convert_month_to_int(const char* month) {
    if (strcasecmp(month, "Jan") == 0) return 0;
    if (strcasecmp(month, "Feb") == 0) return 1;
    if (strcasecmp(month, "Mar") == 0) return 2;
    if (strcasecmp(month, "Apr") == 0) return 3;
    if (strcasecmp(month, "Mei") == 0) return 4;
    if (strcasecmp(month, "Jun") == 0) return 5;
    if (strcasecmp(month, "Jul") == 0) return 6;
    if (strcasecmp(month, "Agu") == 0) return 7;
    if (strcasecmp(month, "Sep") == 0) return 8;
    if (strcasecmp(month, "Okt") == 0) return 9;
    if (strcasecmp(month, "Nov") == 0) return 10;
    if (strcasecmp(month, "Des") == 0) return 11;
    return -1; // Jika bulan tidak valid
}

// Implementasi strptime sederhana
char *my_strptime(const char *buf, const char *format, struct tm *tm) {
    memset(tm, 0, sizeof(struct tm));
    char *ret = NULL;
    if (strcmp(format, "%d-%b-%y") == 0) {
        ret = (char *)buf;
        char month[4] = {0};
        int year;
        if (sscanf(buf, "%2d-%3s-%2d", &tm->tm_mday, month, &year) == 3) {
            // Convert month to lowercase
            for (char *p = month; *p; ++p) *p = tolower(*p);

            // Map abbreviated month to tm_mon
            tm->tm_mon = convert_month_to_int(month);
            tm->tm_year = year + 100; // Karena year 00 adalah 2000, 23 adalah 2023
            ret = ret + 9; // move pointer to the end of parsed date
        }
    } else if (strcmp(format, "%d %B %Y") == 0) {
        ret = (char *)buf;
        char month[10];
        int year;
        if (sscanf(buf, "%2d %9s %4d", &tm->tm_mday, month, &year) == 3) {
            // Convert month name to month number
            const char *english_month = convert_month(month);
            strncpy(month, english_month, sizeof(month));
            tm->tm_mon = convert_month_to_int(month);
            tm->tm_year = year - 1900;
            ret = ret + strlen(buf); // move pointer to the end of parsed date
        }
    }
    if (ret && *ret != '\0') ret = NULL; // parsing failed
    return ret;
}

// Fungsi untuk parsing tanggal dengan dua format berbeda
int parse_date(const char *date_str, struct tm *date) {
    char *ret;
    memset(date, 0, sizeof(struct tm));

    // Coba parsing format pertama: DD-MMM-YY
    ret = my_strptime(date_str, "%d-%b-%y", date);
    if (ret && *ret == '\0') return 1;

    // Coba parsing format kedua: DD MMMM YYYY
    ret = my_strptime(date_str, "%d %B %Y", date);
    if (ret && *ret == '\0') return 1;

    // Parsing gagal
    return 0;
}

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
    scanf(" %19[^\n]", patient_id);

    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].patient_id, patient_id) == 0) {
            printf("Enter new Full Name: ");
            scanf(" %99[^\n]", patients[i].full_name);
            printf("Enter new Address: ");
            scanf(" %149[^\n]", patients[i].address);
            printf("Enter new City: ");
            scanf(" %49[^\n]", patients[i].city);
            printf("Enter new Birth Place: ");
            scanf(" %49[^\n]", patients[i].birth_place);
            printf("Enter new Birth Date (DD MMM YYYY): ");
            scanf(" %29[^\n]", patients[i].birth_date);
            printf("Enter new Age: ");
            scanf("%d", &patients[i].age);
            printf("Enter new BPJS Number: ");
            scanf(" %19[^\n]", patients[i].bpjs_number);

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
    scanf(" %19[^\n]", patient_id);

    int found = 0;
    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].patient_id, patient_id) == 0) {
            found = 1;
            // Shift remaining patients left to overwrite the deleted patient
            for (int j = i; j < patient_count - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patient_count--;
            break;
        }
    }

    if (found) {
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
    } else {
        printf("Patient not found.\n");
    }
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
    /*
    Fungsi untuk mengenerate statistik: 
    - Menerima input "year" dan digunakan data "record"
    - Mengprint jumlah pasien tiap bulan untuk suatu "year"
    - Mengprint total pasien pada suatu "year"  
    - mengprint jumlah pasien tiap suatu diagnosis pada suatu "year"
    */

   //Input tahun dan insialasisi variable yang digunakan
    int year;
    printf("Enter year for patient statistics: ");
    scanf("%d", &year);

    int monthly_patient_count[12] = {0};
    int total_patient_count = 0;

    char diagnoses[MAX_RECORDS][100];
    int diagnosis_count[MAX_RECORDS] = {0};
    int diagnosis_index = 0;

    for (int i = 0; i < record_count; i++) {
        //
        struct tm visit_date = {0};
        parse_date(records[i].visit_date ,&visit_date );
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
    int day, month, year;
    int count = 0;
    printf("\nEnter the date (DD MM YY) to check follow-ups: ");
    scanf("%d %d %d", &day, &month, &year);

    struct tm input_date = {0};
    input_date.tm_mday = day;
    input_date.tm_mon = month - 1; // tm_mon is 0-11
    input_date.tm_year = year + 100; // Karena year 00 adalah 2000, 23 adalah 2023

    time_t now = mktime(&input_date);

    printf("Patients who need follow-up as of %02d-%02d-%02d:\n", day, month, year);
    for (int i = 0; i < record_count; i++) {
        struct tm follow_up_date = {0};
        if (parse_date(records[i].follow_up_date, &follow_up_date)) {
            time_t follow_up_time = mktime(&follow_up_date);
            if (difftime(follow_up_time, now) >= 0) {
                count ++;
                printf("%2d. %s ",(i), records[i].patient_id);
                printf(" %02d-%02d-%02d\n", follow_up_date.tm_mday, follow_up_date.tm_mon + 1, follow_up_date.tm_year % 100); 
            } 
            
        } else {
            printf("Failed to parse date: %s\n", records[i].follow_up_date); 
        }
    }
    
    if (count == 0){
        printf("No follow-up schedule.\n");
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
