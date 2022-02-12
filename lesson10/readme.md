# Power Use Worksheet
>
| 1. What are the different states the device can be in?  |
|---------------------------------------------------------|
| System running idle                                     |    
| Cooking                                                 |
|                                                         |
|    optional: LCD on/off,                                |

| 2. How much will your device be in each state?          |
|---------------------------------------------------------|
| System running idle, unless I implement sleep mode.     |
| Cooking 30 min - 4 hours                                |

| 3. How much current is used in each state? | mA   |
|--------------------------------------------|------|        
| System running idle                        | 17   |
| PWM LED                                    | 2    |
| Solid State Relay        (not wired yet)   | est 2|
| LCD (w/o backlight)      (not wired yet)   | est 6|

| 4. How long will the device last given a 40mAh battery? | Minutes |
|---------------------------------------------------------|---------|
| Idle                                                    | 141     |
| Idle w display                                          | est 104 |
| Cooking w display                                       | est 89  |

**... what size of a meat can you cook with a 3.3V/ 40mA battery ?**

