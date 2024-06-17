#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATIENTS 1000
#define MAX_RECORDS 1000

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

// Fungsi untuk menambahkan pasien baru
void add_patient(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Add Patient", GTK_WINDOW(data), flags, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    // Create grid to arrange labels and entries
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *id_label = gtk_label_new("ID:");
    GtkWidget *id_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 1, 1);

    GtkWidget *name_label = gtk_label_new("Full Name:");
    GtkWidget *name_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), name_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 1, 1, 1);

    GtkWidget *address_label = gtk_label_new("Address:");
    GtkWidget *address_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), address_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), address_entry, 1, 2, 1, 1);

    GtkWidget *city_label = gtk_label_new("City:");
    GtkWidget *city_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), city_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), city_entry, 1, 3, 1, 1);

    GtkWidget *birth_place_label = gtk_label_new("Birth Place:");
    GtkWidget *birth_place_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), birth_place_label, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), birth_place_entry, 1, 4, 1, 1);

    GtkWidget *birth_date_label = gtk_label_new("Birth Date (DD MMM YYYY):");
    GtkWidget *birth_date_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), birth_date_label, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), birth_date_entry, 1, 5, 1, 1);

    GtkWidget *age_label = gtk_label_new("Age:");
    GtkWidget *age_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), age_label, 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), age_entry, 1, 6, 1, 1);

    GtkWidget *bpjs_label = gtk_label_new("BPJS Number:");
    GtkWidget *bpjs_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), bpjs_label, 0, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), bpjs_entry, 1, 7, 1, 1);

    GtkWidget *patient_id_label = gtk_label_new("Patient ID:");
    GtkWidget *patient_id_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), patient_id_label, 0, 8, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), patient_id_entry, 1, 8, 1, 1);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_OK) {
        Patient p;
        p.id = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));
        strcpy(p.full_name, gtk_entry_get_text(GTK_ENTRY(name_entry)));
        strcpy(p.address, gtk_entry_get_text(GTK_ENTRY(address_entry)));
        strcpy(p.city, gtk_entry_get_text(GTK_ENTRY(city_entry)));
        strcpy(p.birth_place, gtk_entry_get_text(GTK_ENTRY(birth_place_entry)));
        strcpy(p.birth_date, gtk_entry_get_text(GTK_ENTRY(birth_date_entry)));
        p.age = atoi(gtk_entry_get_text(GTK_ENTRY(age_entry)));
        strcpy(p.bpjs_number, gtk_entry_get_text(GTK_ENTRY(bpjs_entry)));
        strcpy(p.patient_id, gtk_entry_get_text(GTK_ENTRY(patient_id_entry)));

        patients[patient_count++] = p;

        FILE *file = fopen("data1.csv", "a");
        if (!file) {
            printf("Could not open file data1.csv for writing\n");
        } else {
            fprintf(file, "%d;%s;%s;%s;%s;%s;%d;%s;%s\n", p.id, p.full_name, p.address, p.city, p.birth_place, p.birth_date, p.age, p.bpjs_number, p.patient_id);
            fclose(file);
            printf("Patient added successfully!\n");
        }
    }

    gtk_widget_destroy(dialog);
}

// Fungsi untuk memperbarui pasien
void update_patient(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Update Patient", GTK_WINDOW(data), flags, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create grid to arrange labels and entries
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *patient_id_label = gtk_label_new("Patient ID to update:");
    GtkWidget *patient_id_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), patient_id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), patient_id_entry, 1, 0, 1, 1);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_OK) {
        char patient_id[20];
        strcpy(patient_id, gtk_entry_get_text(GTK_ENTRY(patient_id_entry)));

        for (int i = 0; i < patient_count; i++) {
            if (strcmp(patients[i].patient_id, patient_id) == 0) {
                GtkWidget *name_label = gtk_label_new("Full Name:");
                GtkWidget *name_entry = gtk_entry_new();
                gtk_grid_attach(GTK_GRID(grid), name_label, 0, 1, 1, 1);
                gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 1, 1, 1);
                gtk_entry_set_text(GTK_ENTRY(name_entry), patients[i].full_name);

                GtkWidget *address_label = gtk_label_new("Address:");
                GtkWidget *address_entry = gtk_entry_new();
                gtk_grid_attach(GTK_GRID(grid), address_label, 0, 2, 1, 1);
                gtk_grid_attach(GTK_GRID(grid), address_entry, 1, 2, 1, 1);
                gtk_entry_set_text(GTK_ENTRY(address_entry), patients[i].address);

                GtkWidget *city_label = gtk_label_new("City:");
                GtkWidget *city_entry = gtk_entry_new();
                gtk_grid_attach(GTK_GRID(grid), city_label, 0, 3, 1, 1);
                gtk_grid_attach(GTK_GRID(grid), city_entry, 1, 3, 1, 1);
                gtk_entry_set_text(GTK_ENTRY(city_entry), patients[i].city);

                GtkWidget *birth_place_label = gtk_label_new("Birth Place:");
                GtkWidget *birth_place_entry = gtk_entry_new();
                gtk_grid_attach(GTK_GRID(grid), birth_place_label, 0, 4, 1, 1);
                gtk_grid_attach(GTK_GRID(grid), birth_place_entry, 1, 4, 1, 1);
                gtk_entry_set_text(GTK_ENTRY(birth_place_entry), patients[i].birth_place);

                GtkWidget *birth_date_label = gtk_label_new("Birth Date (DD MMM YYYY):");
                GtkWidget *birth_date_entry = gtk_entry_new();
                gtk_grid_attach(GTK_GRID(grid), birth_date_label, 0, 5, 1, 1);
                gtk_grid_attach(GTK_GRID(grid), birth_date_entry, 1, 5, 1, 1);
                gtk_entry_set_text(GTK_ENTRY(birth_date_entry), patients[i].birth_date);

                GtkWidget *age_label = gtk_label_new("Age:");
                GtkWidget *age_entry = gtk_entry_new();
                gtk_grid_attach(GTK_GRID(grid), age_label, 0, 6, 1, 1);
                gtk_grid_attach(GTK_GRID(grid), age_entry, 1, 6, 1, 1);
                gtk_entry_set_text(GTK_ENTRY(age_entry), g_strdup_printf("%d", patients[i].age));

                GtkWidget *bpjs_label = gtk_label_new("BPJS Number:");
                GtkWidget *bpjs_entry = gtk_entry_new();
                gtk_grid_attach(GTK_GRID(grid), bpjs_label, 0, 7, 1, 1);
                gtk_grid_attach(GTK_GRID(grid), bpjs_entry, 1, 7, 1, 1);
                gtk_entry_set_text(GTK_ENTRY(bpjs_entry), patients[i].bpjs_number);

                GtkWidget *new_patient_id_label = gtk_label_new("Patient ID:");
                GtkWidget *new_patient_id_entry = gtk_entry_new();
                gtk_grid_attach(GTK_GRID(grid), new_patient_id_label, 0, 8, 1, 1);
                gtk_grid_attach(GTK_GRID(grid), new_patient_id_entry, 1, 8, 1, 1);
                gtk_entry_set_text(GTK_ENTRY(new_patient_id_entry), patients[i].patient_id);

                gtk_widget_show_all(dialog);
                response = gtk_dialog_run(GTK_DIALOG(dialog));

                if (response == GTK_RESPONSE_OK) {
                    strcpy(patients[i].full_name, gtk_entry_get_text(GTK_ENTRY(name_entry)));
                    strcpy(patients[i].address, gtk_entry_get_text(GTK_ENTRY(address_entry)));
                    strcpy(patients[i].city, gtk_entry_get_text(GTK_ENTRY(city_entry)));
                    strcpy(patients[i].birth_place, gtk_entry_get_text(GTK_ENTRY(birth_place_entry)));
                    strcpy(patients[i].birth_date, gtk_entry_get_text(GTK_ENTRY(birth_date_entry)));
                    patients[i].age = atoi(gtk_entry_get_text(GTK_ENTRY(age_entry)));
                    strcpy(patients[i].bpjs_number, gtk_entry_get_text(GTK_ENTRY(bpjs_entry)));
                    strcpy(patients[i].patient_id, gtk_entry_get_text(GTK_ENTRY(new_patient_id_entry)));

                    FILE *file = fopen("data1.csv", "w");
                    if (!file) {
                        printf("Could not open file data1.csv for writing\n");
                    } else {
                        for (int j = 0; j < patient_count; j++) {
                            fprintf(file, "%d;%s;%s;%s;%s;%s;%d;%s;%s\n", patients[j].id, patients[j].full_name, patients[j].address, patients[j].city, patients[j].birth_place, patients[j].birth_date, patients[j].age, patients[j].bpjs_number, patients[j].patient_id);
                        }
                        fclose(file);
                        printf("Patient updated successfully!\n");
                    }
                }
                break;
            }
        }
    }

    gtk_widget_destroy(dialog);
}

// Fungsi untuk menampilkan daftar pasien
// Fungsi untuk menghapus data pasien
void delete_patient(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Delete Patient", GTK_WINDOW(data), flags, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *id_label = gtk_label_new("Enter Patient ID:");
    GtkWidget *id_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 1, 1);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_OK) {
        const char *patient_id = gtk_entry_get_text(GTK_ENTRY(id_entry));
        int patient_index = -1;

        for (int i = 0; i < patient_count; i++) {
            if (strcmp(patients[i].patient_id, patient_id) == 0) {
                patient_index = i;
                break;
            }
        }

        if (patient_index != -1) {
            for (int i = patient_index; i < patient_count - 1; i++) {
                patients[i] = patients[i + 1];
            }
            patient_count--;

            FILE *file = fopen("data1.csv", "w");
            if (file) {
                for (int i = 0; i < patient_count; i++) {
                    fprintf(file, "%d;%s;%s;%s;%s;%s;%d;%s;%s\n", patients[i].id, patients[i].full_name, patients[i].address, patients[i].city, patients[i].birth_place, patients[i].birth_date, patients[i].age, patients[i].bpjs_number, patients[i].patient_id);
                }
                fclose(file);
            }
        } else {
            GtkWidget *error_dialog;
            error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Patient ID not found.");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        }
    }

    gtk_widget_destroy(dialog);
}

void search_patient(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Search Patient", GTK_WINDOW(data), flags, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *id_label = gtk_label_new("Enter Patient ID:");
    GtkWidget *id_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 1, 1);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_OK) {
        const char *patient_id = gtk_entry_get_text(GTK_ENTRY(id_entry));
        int patient_index = -1;

        for (int i = 0; i < patient_count; i++) {
            if (strcmp(patients[i].patient_id, patient_id) == 0) {
                patient_index = i;
                break;
            }
        }

        if (patient_index != -1) {
            char patient_info[256];
            snprintf(patient_info, sizeof(patient_info), "ID: %d, Name: %s, Address: %s, City: %s, Birth Place: %s, Birth Date: %s, Age: %d, BPJS Number: %s, Patient ID: %s",
                     patients[patient_index].id, patients[patient_index].full_name, patients[patient_index].address, patients[patient_index].city, patients[patient_index].birth_place, patients[patient_index].birth_date, patients[patient_index].age, patients[patient_index].bpjs_number, patients[patient_index].patient_id);

            GtkWidget *info_dialog;
            info_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", patient_info);
            gtk_dialog_run(GTK_DIALOG(info_dialog));
            gtk_widget_destroy(info_dialog);
        } else {
            GtkWidget *error_dialog;
            error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Patient ID not found.");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        }
    }

    gtk_widget_destroy(dialog);
}



// Fungsi untuk menambahkan rekam medis baru
void add_medical_record(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Add Medical Record", GTK_WINDOW(data), flags, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create grid to arrange labels and entries
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *id_label = gtk_label_new("ID:");
    GtkWidget *id_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 1, 1);

    GtkWidget *visit_date_label = gtk_label_new("Visit Date (DD MMM YYYY):");
    GtkWidget *visit_date_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), visit_date_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), visit_date_entry, 1, 1, 1, 1);

    GtkWidget *patient_id_label = gtk_label_new("Patient ID:");
    GtkWidget *patient_id_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), patient_id_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), patient_id_entry, 1, 2, 1, 1);

    GtkWidget *diagnosis_label = gtk_label_new("Diagnosis:");
    GtkWidget *diagnosis_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), diagnosis_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), diagnosis_entry, 1, 3, 1, 1);

    GtkWidget *treatment_label = gtk_label_new("Treatment:");
    GtkWidget *treatment_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), treatment_label, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), treatment_entry, 1, 4, 1, 1);

    GtkWidget *follow_up_date_label = gtk_label_new("Follow-Up Date (DD MMM YYYY):");
    GtkWidget *follow_up_date_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), follow_up_date_label, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), follow_up_date_entry, 1, 5, 1, 1);

    GtkWidget *cost_label = gtk_label_new("Cost:");
    GtkWidget *cost_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), cost_label, 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cost_entry, 1, 6, 1, 1);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_OK) {
        MedicalRecord r;
        r.id = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));
        strcpy(r.visit_date, gtk_entry_get_text(GTK_ENTRY(visit_date_entry)));
        strcpy(r.patient_id, gtk_entry_get_text(GTK_ENTRY(patient_id_entry)));
        strcpy(r.diagnosis, gtk_entry_get_text(GTK_ENTRY(diagnosis_entry)));
        strcpy(r.treatment, gtk_entry_get_text(GTK_ENTRY(treatment_entry)));
        strcpy(r.follow_up_date, gtk_entry_get_text(GTK_ENTRY(follow_up_date_entry)));
        r.cost = atof(gtk_entry_get_text(GTK_ENTRY(cost_entry)));

        records[record_count++] = r;

        FILE *file = fopen("data2.csv", "a");
        if (!file) {
            printf("Could not open file data2.csv for writing\n");
        } else {
            fprintf(file, "%d;%s;%s;%s;%s;%s;%.2f\n", r.id, r.visit_date, r.patient_id, r.diagnosis, r.treatment, r.follow_up_date, r.cost);
            fclose(file);
            printf("Medical record added successfully!\n");
        }
    }

    gtk_widget_destroy(dialog);
}

// Fungsi untuk menampilkan rekam medis pasien
void show_medical_record(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Show Medical Record", GTK_WINDOW(data), flags, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create grid to arrange labels and entries
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *id_label = gtk_label_new("Enter Patient ID:");
    GtkWidget *id_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 1, 1);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_OK) {
        const char *patient_id = gtk_entry_get_text(GTK_ENTRY(id_entry));
        char record_text[5000] = "";

        for (int i = 0; i < record_count; i++) {
            if (strcmp(records[i].patient_id, patient_id) == 0) {
                char record_info[300];
                snprintf(record_info, sizeof(record_info), "ID: %d, Visit Date: %s, Diagnosis: %s, Treatment: %s, Follow-Up Date: %s, Cost: %.2f\n",
                         records[i].id, records[i].visit_date, records[i].diagnosis, records[i].treatment, records[i].follow_up_date, records[i].cost);
                strcat(record_text, record_info);
            }
        }

        GtkWidget *record_label = gtk_label_new(record_text);
        gtk_label_set_justify(GTK_LABEL(record_label), GTK_JUSTIFY_LEFT);
        gtk_container_add(GTK_CONTAINER(content_area), record_label);
        gtk_widget_show_all(dialog);
        gtk_dialog_run(GTK_DIALOG(dialog));
    }

    gtk_widget_destroy(dialog);
}

// Fungsi untuk menghapus rekam medis pasien berdasarkan ID
void delete_medical_record(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Delete Medical Record", GTK_WINDOW(data), flags, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create grid to arrange labels and entries
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *id_label = gtk_label_new("Enter Patient ID:");
    GtkWidget *id_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 1, 1);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_OK) {
        const char *patient_id = gtk_entry_get_text(GTK_ENTRY(id_entry));

        for (int i = 0; i < record_count; i++) {
            if (strcmp(records[i].patient_id, patient_id) == 0) {
                for (int j = i; j < record_count - 1; j++) {
                    records[j] = records[j + 1];
                }
                record_count--;

                FILE *file = fopen("data2.csv", "w");
                if (!file) {
                    printf("Could not open file data2.csv for writing\n");
                } else {
                    for (int j = 0; j < record_count; j++) {
                        fprintf(file, "%d;%s;%s;%s;%s;%s;%.2f\n", records[j].id, records[j].visit_date, records[j].patient_id, records[j].diagnosis, records[j].treatment, records[j].follow_up_date, records[j].cost);
                    }
                    fclose(file);
                    printf("Medical record deleted successfully!\n");
                }
                break;
            }
        }
    }

    gtk_widget_destroy(dialog);
}

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

// Fungsi untuk menghasilkan laporan pendapatan
void generate_income_report(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Generate Income Report", GTK_WINDOW(data), flags, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *year_label = gtk_label_new("Enter Year:");
    GtkWidget *year_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), year_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), year_entry, 1, 0, 1, 1);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_OK) {
        const char *year_text = gtk_entry_get_text(GTK_ENTRY(year_entry));
        int year = atoi(year_text);

        int monthly_income[12] = {0};
        double yearly_income = 0;
        int search_year;
        int search_bulan;

        for (int i = 0; i < record_count; i++) {
            char charbulan[4] = {0};
            char charyear[5] = {0};
            strncpy(charyear, &records[i].visit_date[strlen(records[i].visit_date) - 4], 4);
            search_year = atoi(charyear);

            if (records[i].visit_date[1] == ' ') {
                strncpy(charbulan, &records[i].visit_date[2], 3);
            } else {
                strncpy(charbulan, &records[i].visit_date[3], 3);
            }
            charbulan[3] = '\0';

            if (strcmp(charbulan, "Jan") == 0) search_bulan = 0;
            else if (strcmp(charbulan, "Feb") == 1) search_bulan = 1;
            else if (strcmp(charbulan, "Mar") == 2) search_bulan = 2;
            else if (strcmp(charbulan, "Apr") == 3) search_bulan = 3;
            else if (strcmp(charbulan, "Mei") == 4) search_bulan = 4;
            else if (strcmp(charbulan, "Jun") == 5) search_bulan = 5;
            else if (strcmp(charbulan, "Jul") == 6) search_bulan = 6;
            else if (strcmp(charbulan, "Agu") == 7) search_bulan = 7;
            else if (strcmp(charbulan, "Sep") == 8) search_bulan = 8;
            else if (strcmp(charbulan, "Okt") == 9) search_bulan = 9;
            else if (strcmp(charbulan, "Nov") == 10) search_bulan = 10;
            else if (strcmp(charbulan, "Des") == 11) search_bulan = 11;

            if (search_year == year) {
                monthly_income[search_bulan] += records[i].cost;
                yearly_income += records[i].cost;
            }
        }

        char report[2048];
        snprintf(report, sizeof(report), "Monthly Income Report for %d:\n", year);
        for (int i = 0; i < 12; i++) {
            char buffer[128];
            snprintf(buffer, sizeof(buffer), "Month %d: %d\n", i + 1, monthly_income[i]);
            strcat(report, buffer);
        }
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "Total Yearly Income: %.2f\n", yearly_income);
        strcat(report, buffer);

        GtkWidget *report_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", report);
        gtk_dialog_run(GTK_DIALOG(report_dialog));
        gtk_widget_destroy(report_dialog);
    }
    gtk_widget_destroy(dialog);
}

// Fungsi untuk menghasilkan statistik pasien
void generate_patient_statistics(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Generate Patient Statistics", GTK_WINDOW(data), flags, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *year_label = gtk_label_new("Enter Year:");
    GtkWidget *year_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), year_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), year_entry, 1, 0, 1, 1);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_OK) {
        const char *year_text = gtk_entry_get_text(GTK_ENTRY(year_entry));
        int year = atoi(year_text);

        int monthly_patient_count[12] = {0};
        int total_patient_count = 0;

        char diagnoses[MAX_RECORDS][100];
        int diagnosis_count[MAX_RECORDS] = {0};
        int diagnosis_index = 0;

        for (int i = 0; i < record_count; i++) {
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

        char report[2048];
        snprintf(report, sizeof(report), "Monthly Patient Count for %d:\n", year);
        for (int i = 0; i < 12; i++) {
            char buffer[128];
            snprintf(buffer, sizeof(buffer), "Month %d: %d\n", i + 1, monthly_patient_count[i]);
            strcat(report, buffer);
        }
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "Total Yearly Patient Count: %d\n", total_patient_count);
        strcat(report, buffer);

        strcat(report, "Diagnosis Statistics:\n");
        for (int i = 0; i < diagnosis_index; i++) {
            char buffer[128];
            snprintf(buffer, sizeof(buffer), "%s: %d\n", diagnoses[i], diagnosis_count[i]);
            strcat(report, buffer);
        }

        GtkWidget *report_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", report);
        gtk_dialog_run(GTK_DIALOG(report_dialog));
        gtk_widget_destroy(report_dialog);
    }
    gtk_widget_destroy(dialog);
}

// Fungsi untuk mengecek follow up pasien
void check_follow_up(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_dialog_new_with_buttons("Check Follow-Up", GTK_WINDOW(data), flags, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    GtkWidget *date_label = gtk_label_new("Enter Date (DD MM YY):");
    GtkWidget *date_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), date_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), date_entry, 1, 0, 1, 1);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_OK) {
        const char *date_text = gtk_entry_get_text(GTK_ENTRY(date_entry));
        int day, month, year;
        sscanf(date_text, "%d %d %d", &day, &month, &year);

        struct tm input_date = {0};
        input_date.tm_mday = day;
        input_date.tm_mon = month - 1; // tm_mon is 0-11
        input_date.tm_year = year + 100; // Karena year 00 adalah 2000, 23 adalah 2023

        time_t now = mktime(&input_date);

        char report[2048];
        snprintf(report, sizeof(report), "Patients who need follow-up as of %02d-%02d-%02d:\n", day, month, year);
        int count = 0;
        for (int i = 0; i < record_count; i++) {
            struct tm follow_up_date = {0};
            if (parse_date(records[i].follow_up_date, &follow_up_date)) {
                time_t follow_up_time = mktime(&follow_up_date);
                if (difftime(follow_up_time, now) >= 0) {
                    char buffer[128];
                    snprintf(buffer, sizeof(buffer), "%2d. %s %02d-%02d-%02d\n", i, records[i].patient_id, follow_up_date.tm_mday, follow_up_date.tm_mon + 1, follow_up_date.tm_year % 100);
                    strcat(report, buffer);
                    count++;
                }
            }
        }
        if (count == 0) {
            strcat(report, "No follow-up schedule.\n");
        }

        GtkWidget *report_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", report);
        gtk_dialog_run(GTK_DIALOG(report_dialog));
        gtk_widget_destroy(report_dialog);
    }
    gtk_widget_destroy(dialog);
}

// Fungsi utama
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Membaca data pasien dari file CSV
    FILE *file = fopen("data1.csv", "r");
    if (!file) {
        printf("Could not open file data1.csv for reading\n");
    } else {
        char line[500];
        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^\n]",
                   &patients[patient_count].id, patients[patient_count].full_name, patients[patient_count].address, patients[patient_count].city,
                   patients[patient_count].birth_place, patients[patient_count].birth_date, &patients[patient_count].age, patients[patient_count].bpjs_number,
                   patients[patient_count].patient_id);
            patient_count++;
        }
        fclose(file);
    }

    // Membaca rekam medis dari file CSV
    file = fopen("data2.csv", "r");
    if (!file) {
        printf("Could not open file data2.csv for reading\n");
    } else {
        char line[500];
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

    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_add_patient, *button_add_record, *button_show_record, *button_delete_record, *button_update_patient, *button_delete_patient, *button_search_patient;
    GtkWidget *generate_income_button, *generate_patient_statistics_button, *check_follow_up_button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Patient Management System");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
    gtk_container_add(GTK_CONTAINER(window), grid);

    button_add_patient = gtk_button_new_with_label("Add Patient");
    g_signal_connect(button_add_patient, "clicked", G_CALLBACK(add_patient), window);
    gtk_grid_attach(GTK_GRID(grid), button_add_patient, 0, 0, 1, 1);

    button_update_patient = gtk_button_new_with_label("Update Patient");
    g_signal_connect(button_update_patient, "clicked", G_CALLBACK(update_patient), window);
    gtk_grid_attach(GTK_GRID(grid), button_update_patient, 0, 1, 1, 1);

    button_delete_patient = gtk_button_new_with_label("Delete Patient");
    g_signal_connect(button_delete_patient, "clicked", G_CALLBACK(delete_patient), window);
    gtk_grid_attach(GTK_GRID(grid), button_delete_patient, 0, 2, 1, 1);

    button_search_patient = gtk_button_new_with_label("Search Patient");
    g_signal_connect(button_search_patient, "clicked", G_CALLBACK(search_patient), window);
    gtk_grid_attach(GTK_GRID(grid), button_search_patient, 0, 3, 1, 1);

    button_add_record = gtk_button_new_with_label("Add Medical Record");
    g_signal_connect(button_add_record, "clicked", G_CALLBACK(add_medical_record), window);
    gtk_grid_attach(GTK_GRID(grid), button_add_record, 1, 0, 1, 1);

    button_show_record = gtk_button_new_with_label("Show Medical Record");
    g_signal_connect(button_show_record, "clicked", G_CALLBACK(show_medical_record), window);
    gtk_grid_attach(GTK_GRID(grid), button_show_record, 1, 1, 1, 1);

    button_delete_record = gtk_button_new_with_label("Delete Medical Record");
    g_signal_connect(button_delete_record, "clicked", G_CALLBACK(delete_medical_record), window);
    gtk_grid_attach(GTK_GRID(grid), button_delete_record, 1, 2, 1, 1);
    
    generate_income_button = gtk_button_new_with_label("Generate Income Report");
    g_signal_connect(generate_income_button, "clicked", G_CALLBACK(generate_income_report), window);
    gtk_grid_attach(GTK_GRID(grid), generate_income_button, 1, 3, 1, 1);

    generate_patient_statistics_button = gtk_button_new_with_label("Generate Patient Statistics");
    g_signal_connect(generate_patient_statistics_button, "clicked", G_CALLBACK(generate_patient_statistics), window);
    gtk_grid_attach(GTK_GRID(grid), generate_patient_statistics_button, 1, 4, 1, 1);

    check_follow_up_button = gtk_button_new_with_label("Check Follow-Up");
    g_signal_connect(check_follow_up_button, "clicked", G_CALLBACK(check_follow_up), window);
    gtk_grid_attach(GTK_GRID(grid), check_follow_up_button, 1, 5, 1, 1);



    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
