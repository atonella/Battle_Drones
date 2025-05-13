## 29.04.2025
- C Compiler Optimierungen

## 06.05.2025
- Projektabgabe:
  - Jederzeit möglich
  - Vor oder nach Prüfungszeitraum (bspw. 01.08.2025)
- GCC 4.2.6
  - 5.3 Labels as Value
  - Sprungtabellen
  - Pro: schnell & praktisch für State Machines
  - Contra: Nur innerhalb von Funktionen
- Noch bessere Alternative: Function pointers
  ```C
  // data type for screen objects

  struct object_t
  {
    // coordinates
    int y;
    int x;
    
    // state machine (function pointer)
    void (*state)(struct object_t* p);
    
    // pointer to vector list data
    struct packet_t* vectors;
    
    // other stuff
    ...
  };

  // sample state: IDLE
  void state_idle(struct object_t* p)
  {
    // ca. 10 Zyklen wenn idle nichts macht (return)
    return
  }

  // sample state: ACTION
  void state_action(struct object_t* p)
  {
    Reset0Ref()
    Moveto_d_7F(p->y, p->x);
    Draw_VLp(p->vectors);
  }

  // data structure holding all game objects
  struct object_t objects[10];

  // sample loop for game action
  while(1)
  {
    WaitRecal();
    Intensity_5F();
    
    // process all objects - slow variant
    for (unsigned int = 0; i < 10; i = i + 1)
    {
      // call state function be means of the function pointer
      objects[i].state(&objects[i]);
    }

    // process all objects - fast variant. Slow: for-loop
    objects[0].state(&objects[0]);
    objects[1].state(&objects[1]);
    objects[2].state(&objects[2]);
    objects[3].state(&objects[3]);
    objects[4].state(&objects[4]);
    objects[5].state(&objects[5]);
    objects[6].state(&objects[6]);
    objects[7].state(&objects[7]);
    objects[8].state(&objects[8]);
    objects[9].state(&objects[9]);
  }







  state = &state_idle;

  state();

  (*state)();






  int matrix[8][4];


  int* i = matrix;

  for (unsigned int y = 0; y < 8; y = y + 1)
  {
    for (unsigned int x = 0; x < 4; x = x + 1)
    {
      if ( *((int*) &maxtrix)[i] == ??)
      {
      }
      i = i +1;
      
      if (*i == ??)
      {
      }
      ++i;
      
      if (matrix[y][x] == ??)
      {
      
      }
    }
  }
  ```

## 13.05.2025
- Kollisionskontrolle
  - Bounding Box
    - einfach: wenige ifs
    - Achtung: Ueberlauf/Unterlauf beachten! Sonst Probleme in den Randbereichen!
  - Bios Routine (objHit() ?)
    - beachtet Ueberlauf/Unterlauf
    - recht gute Performanz
  - C
    - basis klasse mit koordinaten + size
    - komposition: klasse für objekt das basis klasse enthält
    - collision funktion bekommt addresse von objekt klasse übergeben -> casting zu basis klasse + zugriff auf koordinate -> Pruefung ob groesser/kleiner
  - Projektile (Anwendung Union)
    - ```C
    // 1 Variante
    struct ship{int y; int x};
    struct bullet{int y; int x};

    void test(){
      struct ship s;
      struct bullet b;

      if (trigger){
        b.y = s.y; // lda s.y; sta b.y
        b.x = s.x; // lda s.x; sta b.x
                  // ca. 16 Zyklen
      }
    }
    
    
     // 2 Variante
    struct ship{
      union{
        struct{
          int y;
          int x;
        };
        long int yx
      }
    };
    struct bullet{
      union{
        struct{
          int y;
          int x;
        };
        long int yx
      }
    };

    void test(){
      struct ship s;
      struct bullet b;

      if (trigger){
        b.yx = s.yx; // ldd s.y, std b.y; 10 Zyklen
      }
      *((long int*))(&b.y)) = * // TODO
    }
    ```