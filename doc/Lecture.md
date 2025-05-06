## 29.04.2025
- C Compiler Optimierungen

## 06.05.2025
- GCC 4.2.6
  - 5.3 Labels as Value
  - Sprungtabellen
  - Pro: schnell & praktisch für State Machines
  - Contra: Nur innerhalb von Funktionen
- Noch bessere Alternative: Function pointers
  ```C
    // Pseudocode
    // Funktionspointer
    struct object_t{
        ...
        void (*state)(struct object_t* p);
        ...vectors...
    }

    void state_idle(struct object_t* p)
    {
        // ca. 10 Zyklen wenn idle nichts macht (return)
        ...
    }
    
    void state_action(struct object_t* p)
    {
        Reset0Ref();
        Moveto(p->y, p->x);
        Draw(p->vectors);
    }

    struct objects_t objects[10];

    while(action)
    {
        for(...)
        {
            objects[i].state(&objects[i]);
        }
        // or hardcoded all objects to save for loop and save runtime CPU time
        /*
        objects[1].state(&objects[i]);
        objects[2].state(&objects[i]);
        ...
        */
    }

  ```
- Projektabgabe:
  - Jederzeit möglich
  - Vor oder nach Prüfungszeitraum (bspw. 01.08.2025)
  - 