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

void render() {
    // Limpiar el framebuffer
    clear();

    // Establecer el color de borrado (clear color)
    setCurrentColor(Color(0, 0, 128));  // Azul marino

    // Crear un vector de puntos para el polígono #2
    std::vector<Vertex2> polygonPoints = {
        {321, 335}, {288, 286}, {339, 251}, {374, 302}
    };

    // Rellenar el polígono #2 en el framebuffer
    const Color fillColor(0, 0, 255);  // Azul
    framebuffer.fillPolygon(polygonPoints, fillColor);

    // Dibujar el polígono #2 en la framebuffer
    const Color outlineColor(255, 255, 255);  // Blanco
    for (size_t i = 0; i < polygonPoints.size() - 1; ++i) {
        const Vertex2& startPoint = polygonPoints[i];
        const Vertex2& endPoint = polygonPoints[i + 1];
        framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor);
    }
    const Vertex2& startPoint = polygonPoints[polygonPoints.size() - 1];
    const Vertex2& endPoint = polygonPoints[0];
    framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor);

    // Renderizar el framebuffer en un archivo BMP
    framebuffer.renderBuffer("out.bmp");
}

int main() {
    render();

    return 0;
}
