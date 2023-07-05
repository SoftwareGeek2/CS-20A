#include "pent.h"

Pent::Pent(int r, int c) {
    m_col = c;
    m_row = r;
    m_height = PENT_SIZE;
    m_width = PENT_SIZE;

    // Allocate space for figure
    m_pattern = new char*[m_height];
    for (int i = 0; i < m_height; i++) {
        m_pattern[i] = new char[m_width];
    }

    // Initialize figure
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            m_pattern[i][j] = ALIVE;
        }
    }
    m_pattern[0][0] = DEAD;
    m_pattern[0][2] = DEAD;
    m_pattern[2][1] = DEAD;
    m_pattern[2][2] = DEAD;
}

Pent::~Pent() {
    for (int i = 0; i < m_height; i++) {
        delete[] m_pattern[i];
    }
    delete[] m_pattern;
}