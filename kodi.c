#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
int numri_studenteve = 0;
int numri_instruktoreve = 0;
int numri_kurseve = 0;
int studente_ne_kurs = 0;
struct Studente{
    int id;
    char emri[20];
    char mbiemer[20];
    char ditelindja[20];
}s[20];
struct Instruktor{
    int id;
    char emer[20];
    char mbiemer[20];
    char ditelindje[20];
    char kurse_qe_zoteron[100];
}I[30];
struct Kurs {
    int id_kursi;
    char data_e_nisjes[20];
    char ditet_e_zhvillimit[20];
    char orari_fillimit[10];
    char kategoria[50];
    int idInstruktori;
}K[100];
struct student_kurs {
    int student_id;
    int course_id;
} s_k[100];


void menu(){
    printf("\n---------------------***SISTEMI ESHTE GATI***----------------------------\n");
    printf("\n [1]-Regjistro student ne sistem ");
    printf("\n [2]-Krijo nje instruktor te ri ");
    printf("\n [3]-Krijo nje kurs te ri ");
    printf("\n [4]-Regjistro nje student ne kurs ");
    printf("\n [5]-Listo te gjitha kurset e krijuara ");
    printf("\n [6]-Listo te gjithe studentet ");
    printf("\n [7]-Listo te gjithe instruktoret ");
    printf("\n [8]-Listo te gjithe femijet e regjistruar ne nje kurs te caktuar ");
    printf("\n [9]-Listo te gjitha kurset qe nje instruktor jep ");
    printf("\n [10]-Listo te gjithe femijet qe nje instruktor ka ");
    printf("\n [11]-Fshi nje instruktor ");
    printf("\n [12]-Fshi nje kurs");
    printf("\n [13]-Cregjistro nje student ");
    printf("\n [14]-Dalja ");
    printf("\n***********************************************************************************************");
    printf("\n|ZGJIDH: ");

}
void ngarko_student() {
    FILE* f = fopen("student.dat", "rb");
    if (f!= NULL) {
        fread(&numri_studenteve, sizeof(int), 1, f);
        fread(s, sizeof(struct Studente), numri_studenteve, f);
        fclose(f);
    }
}

void save_students() {
    FILE* f = fopen("student.dat", "wb");
    fwrite(&numri_studenteve, sizeof(int), 1, f);
    fwrite(s, sizeof(struct Studente), numri_studenteve, f);
    fclose(f);
}
bool eshte_moshe_e_lejuar(char* ditelindja) {
    int viti, muaji, dita;
    if (sscanf(ditelindja, "%d-%d-%d", &viti, &muaji, &dita) != 3) {
        return false;
    }
    int viti_aktual, muaji_aktual, dita_aktuale;
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    viti_aktual = tm->tm_year + 1900;
    muaji_aktual = tm->tm_mon + 1;
    dita_aktuale = tm->tm_mday;
    int mosha = viti_aktual - viti;
    if (muaji_aktual < muaji || (muaji_aktual == muaji && dita_aktuale < dita)) {
        mosha--;
    }
    return mosha >=5 && mosha <= 14;
}
bool eshte_regjistruar_me_pare(int id) {
    for (int i = 0; i < numri_studenteve; i++) {
        if (s[i].id == id) {
            return true;
        }
    }
    return false;
}
void regjitstro_student_ne_sistem(){
    printf("------------PROCESI PER TE FUTUR TE DHENAT E STUDENTEVE ESHTE GATI-----------------\n");
    int id;
    printf("\n Fut ID: ");
    scanf("%d" , &id); 
    if (eshte_regjistruar_me_pare(id)){ 
        printf("Studenti me kete ID eshte regjistruar me pare ne sistem.\n");
        return;
    }
    s[numri_studenteve].id = id;
    printf("\n Fut emrin: ");
    scanf("%s" , &s[numri_studenteve].emri);
    printf("\n Fut mbiemrin: ");
    scanf("%s" , &s[numri_studenteve].mbiemer);
    printf("\n Fut ditelindjen[YYYY-MM-DD]: ");
    scanf("%s" , &s[numri_studenteve].ditelindja);
    if (!eshte_moshe_e_lejuar(s[numri_studenteve].ditelindja)) {
        printf("Studenti nuk eshte brenda limiteve te lejuara te moshes.\n");
        return;
    }
    numri_studenteve++;
    save_students();
    printf("--STUDENTI U REGJISTRUA NE SISTEM ME SUKSES--");
}
void ngarko_instruktor() {
    FILE* f = fopen("instruktor.dat", "rb");
    if (f!= NULL) {
        fread(&numri_instruktoreve, sizeof(int), 1, f);
        fread(I, sizeof(struct Instruktor), numri_instruktoreve, f);
        fclose(f);
    }
}
void save_instruktor() {
    FILE *f = fopen("intruktore.dat", "wb"); 
    fwrite(&numri_instruktoreve, sizeof(int), 1, f);
    fwrite(I, sizeof(struct Instruktor), numri_instruktoreve, f);
    fclose(f);
}
void krijo_instruktor() {
    printf("------------PROCESI PER TE FUTUR TE DHENAT E INSTRUKTORIT ESHTE GATI-----------------\n");
    printf("Fut ID: ");
    scanf("%d", &I[numri_instruktoreve].id);
    printf("Fut emrin: ");
    scanf("%s", I[numri_instruktoreve].emer);
    printf("Fut mbiemrin: ");
    scanf("%s", I[numri_instruktoreve].mbiemer);
    printf("Fut ditelindjen[YYYY-MM-DD]: ");
    scanf("%s", I[numri_instruktoreve].ditelindje);
    printf("Fut kategorite e kurseve qe zoteron(!NOTE:Ndaj me presje): ");
    char kategori_instruktor[50];
    getchar(); 
    fgets(kategori_instruktor, sizeof(kategori_instruktor), stdin); 
    kategori_instruktor[strcspn(kategori_instruktor, "\n")] = 0; 
    strcpy(I[numri_instruktoreve].kurse_qe_zoteron, kategori_instruktor);
    numri_instruktoreve++;
    save_instruktor();
    printf("--INSTRUKTORI U KRIJUA ME SUKSES--\n");

}
void ngarko_courses() {
    FILE* f = fopen("kurse.dat", "rb");
    if (f!= NULL) {
    fread(&numri_kurseve, sizeof(int), 1, f);
    fread(K, sizeof(struct Kurs), numri_kurseve, f);
    fclose(f);
    }
}
void save_Kurs() {
    FILE* f = fopen("kurse.dat", "wb");
    fwrite(&numri_kurseve, sizeof(int), 1, f);
    fwrite(K, sizeof(struct Kurs), numri_kurseve, f);
    fclose(f);
}
bool kategoria_perputhet(const char *kategoria) {
    const char *kategorite_e_lejuara[] = {"Programim", "Grafik Dizajn", "Robotike"};
    for (int i = 0; i < sizeof(kategorite_e_lejuara) / sizeof(kategorite_e_lejuara[0]); i++) {
        if (strcmp(kategoria, kategorite_e_lejuara[i]) == 0) {
            return true;
        }
    }
    return false;
}
void krijo_kurs() {
    printf("Fut ID: ");
    scanf("%d", &K[numri_kurseve].id_kursi);
    printf("Fut daten e fillimit (YYYY-MM-DD): ");
    scanf("%s", K[numri_kurseve].data_e_nisjes);
    printf("Shkruaj emrin e ditës së javës: ");
    char ditet[50];
    getchar();
    fgets(ditet, sizeof(ditet), stdin); 
    ditet[strcspn(ditet, "\n")] = 0;
    strcpy(K[numri_kurseve].ditet_e_zhvillimit, ditet);
    printf("Fut orarin e fillimit [HH:MM]: ");
    scanf("%s", K[numri_kurseve].orari_fillimit);
    printf("Fut kategorine e kursit (Progrmaim, Grafik Dizajn, Robotike): ");
    char kategoria[50];
    getchar(); 
    fgets(kategoria, sizeof(kategoria), stdin);
    kategoria[strcspn(kategoria, "\n")] = 0; 
    strcpy(K[numri_kurseve].kategoria, kategoria);
    int id_instruktori;
    printf("Jep ID e instruktorit: ");
    scanf("%d", &id_instruktori);
    bool gjetur = false;
    for (int i = 0; i < numri_instruktoreve; i++) {
        if (I[i].id == id_instruktori) {
            gjetur = true;
            if (!kategoria_perputhet(K[numri_kurseve].kategoria)) {
                printf("Kategoria e kursit nuk perputhet me kategorine e instruktorit.\n");
                return;
            }
            break;
        }
    }
    K[numri_kurseve].idInstruktori = id_instruktori;
     if (!gjetur) {
        printf("Instruktori nuk gjendet nuk mund te krijohet kurs.\n");
        return;
    }
    numri_kurseve++;
    save_Kurs();
    printf("--KURSI U KRIJUA ME SUKSES--");
}
void save_student_kurs() {
    FILE* f = fopen("student_kurs.dat", "wb");
    fwrite(&studente_ne_kurs, sizeof(int), 1, f);
    fwrite(s_k, sizeof(struct student_kurs), studente_ne_kurs, f);
    fclose(f);
}
void ngarko_student_kurs() {
    FILE* f = fopen("student_kurs.dat", "rb");
    if (f!= NULL) {
    fread(&studente_ne_kurs, sizeof(int), 1, f);
    fread(s_k, sizeof(struct student_kurs), studente_ne_kurs, f);
    fclose(f);
    }
}
void regjistro_student_ne_kurs() {
    int student_id, course_id;
    printf("Fut ID e studentit: ");
    scanf("%d", &student_id);

    printf("Fut ID e kursit: ");
    scanf("%d", &course_id);
    bool student_gjetur = false;
    int student_index = -1; 
    for (int i = 0; i < numri_studenteve; i++) {
        if (s[i].id == student_id) {
            student_gjetur = true;
            student_index = i; 
            break;
        }
    }

    if (!student_gjetur) {
        printf("Studenti nuk gjendet, nuk mund të kryhet regjistrimi.\n");
        return;
    }
    bool kurs_gjetur = false;
    int kurs_index = -1; 
    for (int i = 0; i < numri_kurseve; i++) {
        if (K[i].id_kursi == course_id) {
            kurs_gjetur = true;
            kurs_index = i; 
            break;
        }
    }

    if (!kurs_gjetur) {
        printf("Kursi nuk gjendet, nuk mund të kryhet regjistrimi.\n");
        return;
    }
    int numri_studenteve_ne_kurs = 0;
    for (int i = 0; i < studente_ne_kurs; i++) {
        if (s_k[i].course_id == kurs_index) { 
            numri_studenteve_ne_kurs++;
            if (s_k[i].student_id == student_index) {
                printf("Studenti është regjistruar më parë në këtë kurs.\n");
                return;
            }
        }
    }

    if (numri_studenteve_ne_kurs >= 6) {
        printf("Kursi është mbushur!\n");
        return;
    }

    // Regjistro studentin në kurs
    s_k[studente_ne_kurs].student_id = student_index;
    s_k[studente_ne_kurs].course_id = kurs_index;

    studente_ne_kurs++;
    save_student_kurs();
    printf("Studenti u regjistrua me sukses në kurs!\n");
}


void listo_të_gjitha_kurset() {
    printf("+----+------------------+---------------------+---------------+---------------+------------------+\n");
    printf("| ID | Data e fillimit | Ditët e zhvillimit | Ora e fillimit|   Kategoria   | ID e instruktorit|\n");
    printf("+----+------------------+---------------------+---------------+---------------+------------------+\n");
    for (int i = 0; i < numri_kurseve; i++) {
        printf("| %2d | %-16s | %-19s | %-13s | %-13s | %d                |\n", 
               K[i].id_kursi, K[i].data_e_nisjes, K[i].ditet_e_zhvillimit, K[i].orari_fillimit, K[i].kategoria, K[i].idInstruktori);
    }
    printf("+----+------------------+---------------------+---------------+---------------+------------------+\n");
}
void listo_të_gjitha_studentet() {
    printf("+------+--------------+--------------+---------------+\n");
    printf("| ID   | Emri         | Mbiemri      | Ditëlindja    |\n");
    printf("+------+--------------+--------------+---------------+\n");
    for (int i = 0; i < numri_studenteve; i++) {
        printf("| %-5d| %-12s| %-12s| %-13s|\n", s[i].id, s[i].emri, s[i].mbiemer, s[i].ditelindja);
    }
    printf("+------+--------------+--------------+---------------+\n");
}

void listo_të_gjithë_instruktoret() {
    printf("+------+-----------------+-----------------+--------------+------------------------------------------------------------+\n");
    printf("| ID   | Emri            | Mbiemri         | Ditëlindja   | Kategoritë                                                 |\n");
    printf("+------+-----------------+-----------------+--------------+------------------------------------------------------------+\n");
    for (int i = 0; i < numri_instruktoreve; i++) {
        printf("| %-5d| %-15s| %-15s| %-12s| %-58s|\n", I[i].id, I[i].emer, I[i].mbiemer, I[i].ditelindje, I[i].kurse_qe_zoteron);
    }
    printf("+------+-----------------+-----------------+--------------+------------------------------------------------------------+\n");
}
void listo_te_gjithe_studentet_ne_kurs() {
    int id_kursit;
    printf("Fut ID e kursit: ");
    scanf("%d", &id_kursit);

    bool gjetur = false;
    for (int i = 0; i < numri_kurseve; i++) {
        if (K[i].id_kursi == id_kursit) {
            gjetur = true;
            break;
        }
    }

    if (!gjetur) {
        printf("Kursi nuk u gjet.\n");
        return;
    }

   printf("ID\tEmër\tMbiemër\tDatëlindja\n");
   for (int i = 0; i < studente_ne_kurs; i++) {
      if (s_k[i].course_id == id_kursit) {
        for (int j = 0; j < numri_studenteve; j++) {
            if (s[j].id == s_k[i].student_id) {
                printf("%d\t%s\t%s\t%s\n", s[j].id, s[j].emri, s[j].mbiemer, s[j].ditelindja);
                break;
            }
        }
    }
   }
} 



void listo_të_gjitha_kurset_e_mësuara_nga_instruktori() {
    int id_instruktori;
    printf("Jepni ID e instruktorit: ");
    scanf("%d", &id_instruktori);

    bool gjetur = false;
    for (int i = 0; i < numri_instruktoreve; i++) {
        if (I[i].id == id_instruktori) {
            gjetur = true;
            break;
        }
    }

    if (!gjetur) {
        printf("Instruktori nuk u gjet.\n");
        return;
    }

    printf("ID\tData e fillimit\tDitët\t\tOra e fillimit\tKategoria\tID e instruktorit\n");
    for (int i = 0; i < numri_kurseve; i++) {
        if (K[i].idInstruktori == id_instruktori) {
            printf("%d\t%s\t%s\t%s\t%s\t%d\n", K[i].id_kursi, K[i].data_e_nisjes, K[i].ditet_e_zhvillimit, K[i].orari_fillimit, K[i].kategoria, K[i].idInstruktori);
        }
    }
}
void listo_te_gjithe_studentet_e_instruktorit() {
    int id_instruktori;
    printf("Vendosni ID e instruktorit: ");
    scanf("%d", &id_instruktori);

    bool gjendet = false;
    for (int i = 0; i < numri_instruktoreve; i++) {
        if (I[i].id == id_instruktori) {
            gjendet = true;
            break;
        }
    }

    if (!gjendet) {
        printf("Instruktori nuk u gjet.\n");
        return;
    }

    printf("ID\tEmri\tMbiemri\tDitëlindja\n");
    for (int i = 0; i < studente_ne_kurs; i++) {
        if (K[s_k[i].course_id].idInstruktori == id_instruktori) {
            for (int j = 0; j < numri_studenteve; j++) {
                if (s[j].id == s_k[i].student_id) {
                    printf("%d\t%s\t%s\t%s\n", s[j].id, s[j].emri, s[j].mbiemer, s[j].ditelindja);
                    break;
                }
            }
        }
    }
}
void fshij_instruktorin() {
    int id_instruktori;
    printf("Vendosni ID e instruktorit: ");
    scanf("%d", &id_instruktori);

    bool gjetur = false;
    for (int i = 0; i < numri_kurseve; i++) {
        if (K[i].idInstruktori == id_instruktori) {
            gjetur = true;
            break;
        }
    }

    if (gjetur) {
        printf("Instruktori ka kurse, nuk mund të fshihet.\n");
        return;
    }

    for (int i = 0; i < numri_instruktoreve; i++) {
        if (I[i].id == id_instruktori) {
            for (int j = i; j < numri_instruktoreve - 1; j++) {
                I[j] = I[j + 1];
            }
            numri_instruktoreve--;
            save_instruktor();
             printf("--INSTRUKTORI U FSHI ME SUKSES--");
            break;
           
        }
    }
}
void fshij_kursin() {
    int id_kursi;
    printf("Vendosni ID e kursit: ");
    scanf("%d", &id_kursi);

    bool gjetur = false;
    for (int i = 0; i < studente_ne_kurs; i++) {
        if (s_k[i].course_id == id_kursi) {
            gjetur = true;
            break;
        }
    }

    if (gjetur) {
        printf("Kursi ka studentë, nuk mund të fshihet.\n");
        return;
    }

    for (int i = 0; i < numri_kurseve; i++) {
        if (K[i].id_kursi == id_kursi) {
            for (int j = i; j < numri_kurseve - 1; j++) {
                K[j] = K[j + 1];
            }
            numri_kurseve--;
            save_Kurs();
            break;
        }
    }
}
void hiq_studentin_nga_kursi() {
    int id_studenti, id_kursi;
    printf("Vendosni ID e studentit: ");
    scanf("%d", &id_studenti);

    printf("Vendosni ID e kursit: ");
    scanf("%d", &id_kursi);

    bool gjetur = false;
    for (int i = 0; i < studente_ne_kurs; i++) {
        if (s_k[i].student_id == id_studenti && s_k[i].course_id == id_kursi) {
            gjetur = true;
            break;
        }
    }

    if (!gjetur) {
        printf("Studenti nuk është i regjistruar në këtë kurs.\n");
        return;
    }

    for (int i = 0; i < studente_ne_kurs; i++) {
        if (s_k[i].student_id == id_studenti && s_k[i].course_id == id_kursi) {
            for (int j = i; j < studente_ne_kurs - 1; j++) {
                s_k[j] = s_k[j + 1];
            }
            studente_ne_kurs--;
            save_student_kurs();
            printf("--STUDENTI U CREGISTRUA ME SUKSES--");
            break;
        }
    }
}

int main() {
    ngarko_student();
    ngarko_instruktor();
    ngarko_courses();
    ngarko_student_kurs();
    int choice;

    do {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                regjitstro_student_ne_sistem();
                break;
            case 2:
                krijo_instruktor();
                break;
            case 3:
                krijo_kurs();
                break;
            case 4:
                regjistro_student_ne_kurs();
                break;
            case 5:
                listo_të_gjitha_kurset();
                break;
            case 6:
                listo_të_gjitha_studentet();
                break;
            case 7:
                listo_të_gjithë_instruktoret();
                break;
            case 8:
                listo_te_gjithe_studentet_ne_kurs();
                break;
            case 9:
                listo_të_gjitha_kurset_e_mësuara_nga_instruktori();
                break;
            case 10:
                listo_te_gjithe_studentet_e_instruktorit();
                break;
            case 11:
                fshij_instruktorin();
                break;
            case 12:
                fshij_kursin();
                break;
            case 13:
                hiq_studentin_nga_kursi();
                break;
            case 14:
                printf("Programi u mbyll.\n");
                break;
            default:
                printf("Zgjedhja nuk është valide. Ju lutem zgjidhni përsëri.\n");
        }
    } while (choice != 14);

    return 0;
}