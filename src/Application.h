#ifndef INC_3DSMIN_APPLICATION_H
#define INC_3DSMIN_APPLICATION_H


class Application {
public:
    Application() = default;
    // Disable copy.
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    // Main loop function.
    int Run();
};


#endif //INC_3DSMIN_APPLICATION_H
