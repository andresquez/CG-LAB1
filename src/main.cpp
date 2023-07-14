#include "vertex.h"
#include "color.h"
#include "framebuffer.h"
#include <vector>
#include <fstream>

// Tamaño del framebuffer
const int FRAMEBUFFER_WIDTH = 800;
const int FRAMEBUFFER_HEIGHT = 600;

// Variables globales
FrameBuffer framebuffer(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
Color clearColor;

void clear() {
    framebuffer.clear(clearColor);
}

void setCurrentColor(const Color& color) {
    clearColor = color;
}

void point(const Vertex2& vertex) {
    int x = static_cast<int>(vertex.x);
    int y = static_cast<int>(vertex.y);

    if (x >= 0 && x < FRAMEBUFFER_WIDTH && y >= 0 && y < FRAMEBUFFER_HEIGHT) {
        framebuffer.setPixel(x, y, clearColor);
    }
}

void poligon3() {
    // Polígono 3
    std::vector<Vertex2> polygonPoints3 = {
        {377, 249}, {411, 197}, {436, 249}
    };

    // Rellenar el polígono 3 en el framebuffer
    const Color fillColor3(255, 0, 0);  // Rojo
    framebuffer.fillPolygon(polygonPoints3, fillColor3);

    // Dibujar el polígono 3 en el framebuffer
    const Color outlineColor3(255, 255, 255);  // Blanco
    for (size_t i = 0; i < polygonPoints3.size() - 1; ++i) {
        const Vertex2& startPoint = polygonPoints3[i];
        const Vertex2& endPoint = polygonPoints3[i + 1];
        framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor3);
    }
    const Vertex2& startPoint = polygonPoints3[polygonPoints3.size() - 1];
    const Vertex2& endPoint = polygonPoints3[0];
    framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor3);
    }

void render() {
    // Limpiar el framebuffer
    clear();

    // Establecer el color de borrado (clear color)
    setCurrentColor(Color(0, 0, 128));  // Azul marino

    poligon3();

    // Renderizar el framebuffer en un archivo BMP
    framebuffer.renderBuffer("out.bmp");
}

int main() {
    render();

    return 0;
}
