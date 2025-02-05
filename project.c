#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX 100
#define USERNAME "admin"
#define PASSWORD "1234"

// Structures to store patient, doctor, and appointment data
typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char medicalHistory[100];
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialty[30];
} Doctor;

typedef struct {
    int patientId;
    int doctorId;
    char appointmentDate[20];
} Appointment;

// Global arrays for storing data
Patient patients[MAX];
Doctor doctors[MAX];
Appointment appointments[MAX];

int patientCount = 0, doctorCount = 0, appointmentCount = 0;

// Function prototypes
void loginPage();
void displayMenu();
void addPatient();
void addDoctor();
void scheduleAppointment();
void displayPatients();
void displayDoctors();
void displayAppointments();
void exitProgram();

// Main function
int main() {
    loginPage(); // User must log in first

    int choice;
    while (1) {
        displayMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                addDoctor();
                break;
            case 3:
                scheduleAppointment();
                break;
            case 4:
                displayPatients();
                break;
            case 5:
                displayDoctors();
                break;
            case 6:
                displayAppointments();
                break;
            case 7:
                exitProgram();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Function to display the login page
void loginPage() {
    char inputUsername[20], inputPassword[20];
    int attempts = 3;

    printf("\n=========== MediCare Management System ===========\n");
    printf("                  User Login Page                 \n");
    while (attempts > 0) {
        printf("\nUsername: ");
        scanf("%s", inputUsername);
        printf("Password: ");
        scanf("%s", inputPassword);

        if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
            printf("\nLogin successful! Welcome to MediCare.\n");
            return;
        } else {
            attempts--;
            printf("Incorrect username or password. Attempts remaining: %d\n", attempts);
        }
    }
    printf("Too many failed attempts. Exiting...\n");
    exit(1);
}

// Function to display the main menu
void displayMenu() {
    printf("\n=========== MediCare Management System ===========\n");
    printf("1. Add Patient\n");
    printf("2. Add Doctor\n");
    printf("3. Schedule Appointment\n");
    printf("4. Display All Patients\n");
    printf("5. Display All Doctors\n");
    printf("6. Display Appointments\n");
    printf("7. Exit\n");
    printf("=================================================\n");
}

// Function to add a new patient
void addPatient() {
    if (patientCount >= MAX) {
        printf("Patient limit reached!\n");
        return;
    }
    printf("\n--- Add New Patient ---\n");
    printf("Enter Patient ID: ");
    scanf("%d", &patients[patientCount].id);
    printf("Enter Name: ");
    scanf(" %[^\n]", patients[patientCount].name);
    printf("Enter Age: ");
    scanf("%d", &patients[patientCount].age);
    printf("Enter Gender: ");
    scanf(" %[^\n]", patients[patientCount].gender);
    printf("Enter Medical History: ");
    scanf(" %[^\n]", patients[patientCount].medicalHistory);
    patientCount++;
    printf("Patient added successfully!\n");
}

// Function to add a new doctor
void addDoctor() {
    if (doctorCount >= MAX) {
        printf("Doctor limit reached!\n");
        return;
    }
    printf("\n--- Add New Doctor ---\n");
    printf("Enter Doctor ID: ");
    scanf("%d", &doctors[doctorCount].id);
    printf("Enter Name: ");
    scanf(" %[^\n]", doctors[doctorCount].name);
    printf("Enter Specialty: ");
    scanf(" %[^\n]", doctors[doctorCount].specialty);
    doctorCount++;
    printf("Doctor added successfully!\n");
}

// Function to schedule an appointment
void scheduleAppointment() {
    if (appointmentCount >= MAX) {
        printf("Appointment limit reached!\n");
        return;
    }
    int patientId, doctorId, i, patientFound = 0, doctorFound = 0;

    printf("\n--- Schedule Appointment ---\n");
    printf("Enter Patient ID: ");
    scanf("%d", &patientId);

    for (i = 0; i < patientCount; i++) {
        if (patients[i].id == patientId) {
            patientFound = 1;
            break;
        }
    }
    if (!patientFound) {
        printf("Patient ID not found!\n");
        return;
    }

    printf("Enter Doctor ID: ");
    scanf("%d", &doctorId);

    for (i = 0; i < doctorCount; i++) {
        if (doctors[i].id == doctorId) {
            doctorFound = 1;
            break;
        }
    }
    if (!doctorFound) {
        printf("Doctor ID not found!\n");
        return;
    }

    printf("Enter Appointment Date (DD/MM/YYYY): ");
    scanf(" %[^\n]", appointments[appointmentCount].appointmentDate);

    appointments[appointmentCount].patientId = patientId;
    appointments[appointmentCount].doctorId = doctorId;
    appointmentCount++;

    printf("Appointment scheduled successfully!\n");
}

// Function to display all patients in table format
void displayPatients() {
    if (patientCount == 0) {
        printf("No patients registered yet!\n");
        return;
    }
    printf("\n--- List of Patients ---\n");
    printf("-----------------------------------------------------------\n");
    printf("| ID   | Name             | Age  | Gender   | Medical History    |\n");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < patientCount; i++) {
        printf("| %-4d | %-16s | %-4d | %-8s | %-18s |\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].gender, patients[i].medicalHistory);
    }
    printf("-----------------------------------------------------------\n");
}

// Function to display all doctors in table format
void displayDoctors() {
    if (doctorCount == 0) {
        printf("No doctors registered yet!\n");
        return;
    }
    printf("\n--- List of Doctors ---\n");
    printf("-----------------------------------------\n");
    printf("| ID   | Name             | Specialty       |\n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("| %-4d | %-16s | %-16s |\n",
               doctors[i].id, doctors[i].name, doctors[i].specialty);
    }
    printf("-----------------------------------------\n");
}

// Function to display all appointments
void displayAppointments() {
    if (appointmentCount == 0) {
        printf("No appointments scheduled yet!\n");
        return;
    }
    printf("\n--- List of Appointments ---\n");
    for (int i = 0; i < appointmentCount; i++) {
        printf("Patient ID: %d, Doctor ID: %d, Date: %s\n",
               appointments[i].patientId, appointments[i].doctorId,
               appointments[i].appointmentDate);
    }
}

// Function to exit the program
void exitProgram() {
    printf("Exiting the MediCare Management System. Goodbye!\n");
exit(0);
}