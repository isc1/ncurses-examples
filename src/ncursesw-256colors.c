#include <ncurses.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");  // For wide character support
    initscr();
    start_color();
    
    if (!has_colors() || !can_change_color()) {
        endwin();
        printf("Your terminal does not support color manipulation.\n");
        return 1;
    }

    // Enable color manipulation
    use_default_colors();
    
    // Create all color pairs - we'll need both foreground and background variants
    for (int i = 0; i < 256; i++) {
        init_pair(i + 1, i, -1);        // Foreground colors (1-256)
        init_pair(i + 257, 7, i);       // Background colors (257-512), white text (7)
    }
    
    clear();
    
    // Display foreground colors
    mvprintw(0, 0, "Foreground colors (text):");
    for (int i = 0; i < 256; i++) {
        int row = 2 + (i / 16);
        int col = (i % 16) * 5;
        attron(COLOR_PAIR(i + 1));
        mvprintw(row, col, "Aa7");
        attroff(COLOR_PAIR(i + 1));
    }
    
    // Display background colors
    mvprintw(18, 0, "Background colors:");
    for (int i = 0; i < 256; i++) {
        int row = 20 + (i / 16);
        int col = (i % 16) * 5;
        attron(COLOR_PAIR(i + 257) | A_NORMAL);  // A_NORMAL to ensure no other attributes
        mvprintw(row, col, "Aa7");
        attroff(COLOR_PAIR(i + 257) | A_NORMAL);
    }
    
    mvprintw(36, 0, "Press any key to exit...");
    refresh();
    getch();
    endwin();
    return 0;
}
