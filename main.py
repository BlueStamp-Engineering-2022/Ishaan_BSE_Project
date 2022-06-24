import time
import bluetooth
import pygame

WHITE = (0, 0, 255)

sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
sock.connect(("98:DA:60:01:94:CD", 1))
time.sleep(1)

pygame.init()
 
size = (700, 500)
screen = pygame.display.set_mode(size)
 
pygame.display.set_caption("My Game")
 
done = False
 
clock = pygame.time.Clock()
 
while not done:
    keys = pygame.key.get_pressed()  
    if keys[pygame.K_w]:
        sock.send("%A#")
    if keys[pygame.K_a]:
        sock.send("%B#")
    if keys[pygame.K_s]:
        sock.send("%D#")
    if keys[pygame.K_d]:
        sock.send("%C#")
    if keys[pygame.K_c]:
        sock.send("%5#")
    if keys[pygame.K_o]:
        sock.send("%6#")

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
 

    screen.fill(WHITE)
 
    pygame.display.flip()
 
    clock.tick(60)
 
pygame.quit()

sock.close()
