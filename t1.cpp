#include <iostream>   
#include <GL/glut.h>       
#include <GL/freeglut.h>    
#include <math.h>  
#include <cstdlib>         
using namespace std; 

//Salma
struct Move {
    float rotate = 0.0;   
    float scale = 1.0;    
    float translateX = 0.0; 
    float translateY = 0.0; 
} donat, coklat, esKulKul;

bool isMoving = true;      
bool is2DMode = false;     
float lightPos[] = {-10.0f, 10.0f, 10.0f, 1.0f}; // Posisi sumber cahaya dalam ruang 3D
int Object = 1;    
bool hiddenCarte = false; 
bool Loading = true;  
float loadingProgress = 0.0; 
const int MAX_CHIPS = 30;
float chocoChips[MAX_CHIPS][3]; // Array 2D untuk menyimpan posisi (x, y, z)

// Salma
void Kartesius() {
    glLineWidth(2.0);
    glBegin(GL_LINES);
    // Sumbu X (Merah)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-50.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    // Sumbu Y (Hijau)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -50.0, 0.0);
    glVertex3f(0.0, 50.0, 0.0);
    // Sumbu Z (Biru)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -50.0);
    glVertex3f(0.0, 0.0, 50.0);
    glEnd();
}

//Fathir
void Text(float x, float y, float z, string text, int fontSize) {
    glColor3ub(0, 255, 0); 
    glPushMatrix();
    glTranslatef(x, y, z);   // Posisi teks
    //glScalef(fontSize / 8.0f, fontSize / 13.0f, 1.0f); // Skala teks
    glRasterPos2f(0, 0);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char *)text.c_str());
    glPopMatrix();
}

//Fathir MS
void LoadingScene() { 
    glPushMatrix();
    Text(-20.0, 0.0, 0.0, "SELAMAT DATANG", 90); // Pesan loading

    glPushMatrix();
    glRotatef(30, 0, 1, 0); // Rotasi progress bar
    glColor3ub(0, 255, 0);  // Warna hijau untuk progress bar
    float progressWidth = (loadingProgress / 100.0) * 40.0; // Hitung lebar sesuai progress
    glTranslatef(-20.0 + progressWidth / 2.0, -2.0, 0.1); // Posisi progress bar
    glScalef(progressWidth, 2.0, 1.0); // Skala bar tergantung progress
    glutSolidCube(1.0); // Bentuk progress bar
    glPopMatrix();

    // Perbarui status loading
    loadingProgress += 0.5;
    if (loadingProgress >= 100.0) {
        Loading = false;  // Hentikan layar loading
        loadingProgress = 0.0;
        Object = 1;    // Default ke objek Donat setelah loading selesai
    }
    glPopMatrix();
}

// Gea
void Background() {
    glDisable(GL_DEPTH_TEST); // Nonaktifkan depth test untuk latar belakang
    glBegin(GL_QUADS);

    // Warna sudut kiri bawah
    glColor3f(0.0f, 0.5f, 0.7f); // Biru kehijauan
    glVertex2f(-1.0f, -1.0f);

    // Warna sudut kanan bawah
    glColor3f(0.0f, 0.3f, 0.5f); // Biru lebih gelap
    glVertex2f(1.0f, -1.0f);

    // Warna sudut kanan atas
    glColor3f(0.5f, 0.8f, 1.0f); // Biru muda
    glVertex2f(1.0f, 1.0f);

    // Warna sudut kiri atas
    glColor3f(0.3f, 0.6f, 0.9f); // Biru sedang
    glVertex2f(-1.0f, 1.0f);

    glEnd();
    glEnable(GL_DEPTH_TEST); // Aktifkan kembali depth test
}

//Fathir
void Donat() {
    glPushMatrix();
    glTranslatef(donat.translateX, donat.translateY, 0.0); // Pindahkan posisi donat
    glRotatef(donat.rotate, 1.0, 0.0, 0.0); // Rotasi horizontal
    glScalef(donat.scale, donat.scale, donat.scale); // Skala donat

    // Warna dasar donat
    glColor3ub(160, 82, 45);
    glutSolidTorus(3.0, 4.0, 50, 50); // Bentuk donat

	//topping seres
    glPushMatrix();
    glColor3ub(255, 255, 255); // Warna putih untuk seres
    glTranslatef(0.0, 0.0, 3.1); // Posisi seres di atas donat
    for (int i = 0; i < 360; i += 30) {
        glPushMatrix();
        glRotatef(i, 0.0, 0.0, 1.0); // Sebar seres di keliling donat
        glTranslatef(4.0, 0.0, 0.0); // Jarak dari pusat (radius luar donat)
        glRotatef(90.0, 1.0, 0.0, 0.0); // Rotasi silinder agar tegak
        glutSolidCylinder(0.1, 0.5, 20, 20); // Bentuk seres (silinder kecil)
        glPopMatrix();
    }
    
    glPopMatrix();

    glPopMatrix();
}

// Salma
void Coklat() {
    glPushMatrix();
    glTranslatef(coklat.translateX, coklat.translateY, 0.0); // Translasi posisi coklat
    glRotatef(coklat.rotate, 0.0, 1.0, 0.0); // Rotasi coklat
    glScalef(coklat.scale, coklat.scale, coklat.scale); // Skala coklat

    // Batang utama coklat
    glColor3ub(139, 69, 19); // 
    glPushMatrix();
    glScalef(10.0, 1.0, 3.0);
    glutSolidCube(1.5);
    glPopMatrix();

    // Segmen-segmen coklat
    glColor3ub(160, 82, 45); 
    for (int i = -4; i <= 4; i++) {
        glPushMatrix();
        glTranslatef(i * 1.6, 1.0, 0.0); // Posisi segmen
        glScalef(1.0, 0.5, 2.5); // Skala segmen
        glutSolidCube(1.5);
        glPopMatrix();
    }
    glPopMatrix();
}

//gea
void RandomChocoChips(int count, float radius)
{
    for (int i = 0; i < count; i++)
    {
        float theta = (float(rand()) / RAND_MAX) * 2.0f * 3.14159f;
        float phi = (float(rand()) / RAND_MAX) * 3.14159f;
        float r = radius;

        // Hitung koordinat berdasarkan sphere mapping
        chocoChips[i][0] = r * sin(phi) * cos(theta); // x
        chocoChips[i][1] = r * sin(phi) * sin(theta); // y
        chocoChips[i][2] = r * cos(phi);              // z
    }
}

void ChocoChips(int count)
{
    glColor3ub(139, 69, 19); // Warna coklat untuk choco chips
    for (int i = 0; i < count; i++)
    {
        glPushMatrix();
        glTranslatef(
            chocoChips[i][0], // x
            chocoChips[i][1], // y
            chocoChips[i][2]  // z
        );
        glutSolidSphere(0.3, 20, 20); // Sphere kecil untuk choco chips
        glPopMatrix();
    }
}

//Gea
void EsKulKul()
{
    glPushMatrix();
    // Terapkan translasi, rotasi, dan skala berdasarkan transformasi esKulKul
    glTranslatef(esKulKul.translateX, esKulKul.translateY, 0.0);
    glRotatef(esKulKul.rotate, 0.0, 1.0, 0.0);
    glScalef(esKulKul.scale, esKulKul.scale, esKulKul.scale);

    // Membalik orientasi es kul-kul
    glRotatef(180, 1.0, 0.0, 0.0);

    // Pindahkan posisi dasar es kul-kul
    glTranslatef(0.0, 18.0, 0.0);

    // Gambar stik es kul-kul
    glPushMatrix();
    glColor3ub(139, 69, 19);              // Warna coklat untuk stik
    glTranslatef(0.0, 0.0, 0.0);          // Posisi stik di bawah es
    glRotatef(90.0, 1.0, 0.0, 0.0);       // Rotasi stik agar vertikal
    glutSolidCylinder(0.5, 10.0, 20, 20); // Bentuk silinder untuk stik

    // Gambar lapisan pertama es kul-kul (biru)
    glColor3ub(135, 206, 250);    // Warna biru muda
    glTranslatef(0.0, 0.0, 10.0); // Pindahkan ke atas stik
    glutSolidSphere(4.0, 50, 50); // Bentuk bola untuk es

    // Gambar lapisan kedua es kul-kul (hijau)
    glColor3ub(34, 139, 34);      // Warna hijau
    glTranslatef(0.0, 0.0, 5.0);  // Pindahkan ke atas lapisan pertama
    glutSolidSphere(4.0, 50, 50); // Bentuk bola kedua

    // Gambar lapisan ketiga es kul-kul (merah muda)
    glColor3ub(255, 105, 180);    // Warna merah muda
    glTranslatef(0.0, 0.0, 5.0);  // Pindahkan ke atas lapisan kedua
    glutSolidSphere(4.0, 50, 50); // Bentuk bola ketiga

    // Tambahkan meises pada lapisan merah muda
    glPushMatrix();
    ChocoChips(MAX_CHIPS);
    glPopMatrix();

    glPopMatrix(); // Selesai menggambar stik dan lapisan es
    glPopMatrix(); // Selesai menggambar es kul-kul
}

// Fathir
void processMenu(int option) {
    switch (option) {
        case 1:
            Object = 1; //donat
            break;
        case 2:
            Object = 2; //coklat
            break;
        case 3:
            Object = 3; //eskulkul
            break;
        case 4:
            exit(0); 
    }
    glutPostRedisplay(); // Refresh tampilan
}

// Salma
void Menu() {
    glutCreateMenu(processMenu); 
    glutAddMenuEntry("Donat", 1); 
    glutAddMenuEntry("Coklat", 2); 
    glutAddMenuEntry("Es Kul-Kul", 3); 
    glutAddMenuEntry("Keluar", 4); 
    glutAttachMenu(GLUT_RIGHT_BUTTON); 
}

// Gea
void update(int value) { 
    if (isMoving) { // Jika animasi diaktifkan
        donat.rotate += 1.0; 
        coklat.rotate += 1.2; 
        esKulKul.rotate += 0.5; 
    }
    glutPostRedisplay(); // Refresh tampilan
    glutTimerFunc(1000 / 60, update, 0); // Jadwalkan pembaruan berikutnya
}

// Gea
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
            if (Object == 1)
                donat.scale += 0.1;
                if (donat.scale >= 2){
                	donat.scale -=0.1;
				}
            else if (Object == 2)
                coklat.scale += 0.1;
                if (coklat.scale >= 2){
                	coklat.scale -=0.1;
				}
            else if (Object == 3)
                esKulKul.scale += 0.1;
                if (esKulKul.scale >= 2){
                	esKulKul.scale -=0.1;
				}
            break;
        case '-':
            // Perkecil skala objek saat tombol '-' ditekan
            if (Object == 1)
                donat.scale -= 0.1;
                if (donat.scale <= 0.5){
                	donat.scale +=0.1;
				}
            else if (Object == 2)
                coklat.scale -= 0.1;
                 if (coklat.scale <= 0.5){
                	coklat.scale +=0.1;
				}
            else if (Object == 3)
                esKulKul.scale -= 0.1;
                if (esKulKul.scale <= 0.5){
                	esKulKul.scale +=0.1;
				}
            break;
        case 'w':
        case 'W':
            // Geser objek ke atas
            if (Object == 1)
                donat.translateY += 1.0;
                if (donat.translateY >= 30){
                	donat.translateY -=1.0;
				}
            else if (Object == 2)
                coklat.translateY += 1.0;
                if (coklat.translateY >= 30){
                	coklat.translateY -=1.0;
				}
            else if (Object == 3)
                esKulKul.translateY += 1.0;
                if (esKulKul.translateY >= 30){
                	esKulKul.translateY -=1.0;
				}
            break;
        case 's':
        case 'S':
            // Geser objek ke bawah
            if (Object == 1)
                donat.translateY -= 1.0;
                if (donat.translateY <= -30){
                	donat.translateY +=1.0;
				}
            else if (Object == 2)
                coklat.translateY -= 1.0;
                if (coklat.translateY <= -30){
                	coklat.translateY +=1.0;
				}
            else if (Object == 3)
                esKulKul.translateY -= 1.0;
                if (esKulKul.translateY <= -30){
                	esKulKul.translateY +=1.0;
				}
            break;
        case 'd':
        case 'D':
            // Geser objek ke kanan
            if (Object == 1)
                donat.translateX += 1.0;
                if (donat.translateX >= 30){
                	donat.translateX -=1.0;
				}
            else if (Object == 2)
                coklat.translateX += 1.0;
                if (coklat.translateX >= 30){
                	coklat.translateX -=1.0;
				}
            else if (Object == 3)
                esKulKul.translateX += 1.0;
                if (esKulKul.translateX >= 30){
                	esKulKul.translateX -=1.0;
				}
            break;
        case 'a':
        case 'A':
            // Geser objek ke kiri
            if (Object == 1)
                donat.translateX -= 1.0;
                if (donat.translateX <= -30){
                	donat.translateX +=1.0;
				}
            else if (Object == 2)
                coklat.translateX -= 1.0;
                if (coklat.translateX <= -30){
                	coklat.translateX +=1.0;
				}
            else if (Object == 3)
                esKulKul.translateX -= 1.0;
                if (esKulKul.translateX <= -30){
                	esKulKul.translateX +=1.0;
				}
            break;
        case 'c':
        case 'C':
//cartesius
            hiddenCarte = !hiddenCarte;
            break;
        case 'r':
        case 'R':
            // rotasi
            isMoving = !isMoving;
            break;
    }
    glutPostRedisplay(); 
}

//Gea
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Bersihkan layar
    glLoadIdentity();

    // Gambar latar belakang terlebih dahulu
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1); // Proyeksi ortogonal untuk background
    Background(); // Gambar gradasi background
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Gambar objek utama di depan background
    if (Loading) {
        LoadingScene(); 
    } else {
        if (hiddenCarte) {
            Kartesius(); 
        }
        switch (Object) {
            case 1:
                Donat(); 
                break;
            case 2:
                Coklat(); 
                break;
            case 3:
                EsKulKul(); 
                break;
        }
    }

    glutSwapBuffers(); 
}

// Salma
void init3D()
{
    glEnable(GL_DEPTH_TEST);     // Aktifkan depth testing untuk memastikan objek 3D terlihat benar
    glEnable(GL_COLOR_MATERIAL); // Aktifkan pengaturan material warna

    RandomChocoChips(MAX_CHIPS, 4.2f);

    // Inisialisasi pencahayaan
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f}; // Cahaya ambient
    GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Cahaya difus
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // Posisi sumber cahaya

    // Pengaturan viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 1.0, 100.0);                     // Perspektif tampilan
    gluLookAt(30.0, 30.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Posisi kamera
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 1.0); 
}

//Fathir
int main(int argc, char **argv) {
    glutInit(&argc, argv); // Inisialisasi GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Pengaturan mode tampilan
    glutInitWindowSize(800, 600); 
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("KELOMPOK 2_TB GRAFKOM_E");  
    init3D(); 
    glutDisplayFunc(display); 
    Menu(); // Buat menu interaktif
    glutKeyboardFunc(keyboard); 
    glutTimerFunc(1000 / 60, update, 0); // Timer untuk pembaruan animasi
    glutMainLoop(); 
    return 0; 
}
