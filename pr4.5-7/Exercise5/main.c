#include <stdio.h>
#include <pwd.h>
#include <errno.h>

int main() {
    // Отримати інформацію про користувача за UID
    uid_t uid = getuid();
    struct passwd *user_by_uid = getpwuid(uid);
    if (user_by_uid == NULL) {
        perror("Помилка отримання інформації за UID");
    } else {
        printf("Інформація про користувача за UID %d:\n", uid);
        printf("Ім'я користувача: %s\n", user_by_uid->pw_name);
        printf("Повне ім'я: %s\n", user_by_uid->pw_gecos);
    }

    // Отримати інформацію про користувача root за реєстраційним ім'ям
    const char *username = "root";
    struct passwd *root_user = getpwnam(username);
    if (root_user == NULL) {
        perror("Помилка отримання інформації про користувача root");
    } else {
        printf("\nІнформація про користувача з ім'ям '%s':\n", username);
        printf("UID: %d\n", root_user->pw_uid);
        printf("Головна група GID: %d\n", root_user->pw_gid);
        printf("Домашній каталог: %s\n", root_user->pw_dir);
    }

    return 0;
}
