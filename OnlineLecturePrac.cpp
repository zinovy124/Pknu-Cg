#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

GLfloat myVertices[8][3] = {
    {-0.25, -0.25, 0.25},
    {-0.25, 0.25, 0.25},
    {0.25, 0.25, 0.25},
    {0.25, -0.25, 0.25},
    {-0.25, -0.25, -0.25},
    {-0.25, 0.25, -0.25},
    {0.25, 0.25, -0.25},
    {0.25, -0.25, -0.25},
};

GLfloat myColors[8][3] = {
    {0.2, 0.2, 0.2},
    {1.0, 0.0, 0.0},
    {1.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 0.0, 1.0},
    {1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0},
};

GLubyte myVertexList[24] = {0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4}; // 내가 바라봤을 때 반시계 방향으로 정점 정하기

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT); // 클리어할 대상을 전달하면 됨, Color Buffer -> 프레임 버퍼를 지운다
    glFrontFace(GL_CCW); // 정점을 정면에서 바라봤을 때 Counter ClockWise(반시계방향) 으로 정의하겠다.
    glEnable(GL_CULL_FACE); // 카메라를 바라봤을 때 보이는 면이냐 아니냐를 판별, 뒤쪽 면은 안 보이니 계산할 필요 없음. 그걸 계산하지 않고 잘라낸다는 변수.
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, myColors);
    glVertexPointer(3, GL_FLOAT, 0, myVertices); // 세 개의 float 값을 myColors, myVertices 가 갖고 있다.
    glMatrixMode(GL_MODELVIEW); // Model View 에 관련된 변환행렬을 바꾸겠다.
    glLoadIdentity(); // 단위행렬로 정의하겠다.
    glRotatef(30.0, 1.0, 1.0, 1.0); // (1, 1, 1) 에서 30도만큼 회전하라
    // 육면체 그리는 for 문.
    for (GLint i = 0; i < 6; i++) {
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &myVertexList[4 * i]); // polygon을 그린다, 네 개의 정점이 있다, unsigned byte의 자료형을 갖고 있다, 정점이 시작되는 정점 배열의 첫 번째 주소
    }
    glFlush(); // 화면의 내용을 바꿔라. 현재 화면에 그려지는 내용을 여기서 보여지는 화면으로 바꿔라.
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Drawing Example");
    glClearColor(1.0, 1.0, 1.0, 1.0); // 도화지 색
    glMatrixMode(GL_PROJECTION); // 투영에 관련된, 변환행렬을 정의하겠다. 투영행렬에 대한 것들을
    glLoadIdentity(); // LoadIdentity로 바꾸겠다. (단위행렬로)
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 여러 투영방법 중 평행투영(디폴트임)을 사용하겠다.
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}