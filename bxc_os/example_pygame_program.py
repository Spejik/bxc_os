import pygame
from random import randrange
from time import time 

# initialize the pygame library
pygame.init()

# set up the drawing window
screenW = 500
screenH = 500
screen = pygame.display.set_mode([screenW, screenH])

# used to draw elapsed time
font = pygame.font.Font(pygame.font.get_default_font(), 36)

# run until the user asks to quit
running = True
started = int(time())
while running:
	
    # close the window after 10 seconds
    if int(time()) - started > 10:
         running = False
    
	# draw the elapsed time
    text_surface = font.render(str(int(time()) - started), True, (250, 250, 250))
    screen.blit(text_surface, dest=(50,50))

    # fill the background with very dark gray
    screen.fill((15, 15, 15))

    # draw a solid circle in the center with a random color
    pygame.draw.circle(screen, (randrange(255), randrange(255), randrange(255)), (int(screenW / 2), int(screenH / 2)), 75)

	# flip the display
    pygame.display.flip()



# quit after the while loop finished
pygame.quit()