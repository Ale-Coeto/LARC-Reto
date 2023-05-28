# LARC-Reto

Movimiento basado en estados: 
- Revisar si aún se deben recorrer unidades
- Recorrer unidades
- Parar

Posición universal del robot basado en lecturas las lecturas de los encoders y el modelo kinemático.

Función de movimiento, hacia el ángulo y orientación indicadas con correcciones de imu.

Lectura de sensores de luz para corregir posiciones finales que puedan terminar sobre la línea.

Clases:
- BNO
- Color (sensores de línea)
- Motor
- Drivetrain
- PID
- Mecanum (main)
