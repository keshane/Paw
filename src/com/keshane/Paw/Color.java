package com.keshane.Paw;

enum Color {
    BLACK,
    WHITE;

    Color opposite() {
        if (this == BLACK) {
            return WHITE;
        }
        else {
            return BLACK;
        }
    }
}
