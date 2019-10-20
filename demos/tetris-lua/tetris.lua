width = 640
height = 480
bpp = 32

--definition of tetris pieces
pieces = {}
for i=1,7 do
	pieces[i] = {}     
	for j=1,4 do
		pieces[i][j] = {}
	end
end

--square 
pieces[1][1][1] = {0,0,0,0,0}
pieces[1][1][2] = {0,0,0,0,0}
pieces[1][1][3] = {0,0,1,1,0}
pieces[1][1][4] = {0,0,1,1,0}
pieces[1][1][5] = {0,0,0,0,0}

pieces[1][2][1] = {0,0,0,0,0}
pieces[1][2][2] = {0,0,0,0,0}
pieces[1][2][3] = {0,0,1,1,0}
pieces[1][2][4] = {0,0,1,1,0}
pieces[1][2][5] = {0,0,0,0,0}

pieces[1][3][1] = {0,0,0,0,0}
pieces[1][3][2] = {0,0,0,0,0}
pieces[1][3][3] = {0,0,1,1,0}
pieces[1][3][4] = {0,0,1,1,0}
pieces[1][3][5] = {0,0,0,0,0}

pieces[1][4][1] = {0,0,0,0,0}
pieces[1][4][2] = {0,0,0,0,0}
pieces[1][4][3] = {0,0,1,1,0}
pieces[1][4][4] = {0,0,1,1,0}
pieces[1][4][5] = {0,0,0,0,0}

--I 
pieces[2][1][1] = {0,0,0,0,0}
pieces[2][1][2] = {0,0,0,0,0}
pieces[2][1][3] = {0,2,2,2,2}
pieces[2][1][4] = {0,0,0,0,0}
pieces[2][1][5] = {0,0,0,0,0}

pieces[2][2][1] = {0,0,0,0,0}
pieces[2][2][2] = {0,0,2,0,0}
pieces[2][2][3] = {0,0,2,0,0}
pieces[2][2][4] = {0,0,2,0,0}
pieces[2][2][5] = {0,0,2,0,0}

pieces[2][3][1] = {0,0,0,0,0}
pieces[2][3][2] = {0,0,0,0,0}
pieces[2][3][3] = {2,2,2,2,0}
pieces[2][3][4] = {0,0,0,0,0}
pieces[2][3][5] = {0,0,0,0,0}

pieces[2][4][1] = {0,0,2,0,0}
pieces[2][4][2] = {0,0,2,0,0}
pieces[2][4][3] = {0,0,2,0,0}
pieces[2][4][4] = {0,0,2,0,0}
pieces[2][4][5] = {0,0,0,0,0}

--L 
pieces[3][1][1] = {0,0,0,0,0}
pieces[3][1][2] = {0,0,3,0,0}
pieces[3][1][3] = {0,0,3,0,0}
pieces[3][1][4] = {0,0,3,3,0}
pieces[3][1][5] = {0,0,0,0,0}

pieces[3][2][1] = {0,0,0,0,0}
pieces[3][2][2] = {0,0,0,0,0}
pieces[3][2][3] = {0,3,3,3,0}
pieces[3][2][4] = {0,3,0,0,0}
pieces[3][2][5] = {0,0,0,0,0}

pieces[3][3][1] = {0,0,0,0,0}
pieces[3][3][2] = {0,3,3,0,0}
pieces[3][3][3] = {0,0,3,0,0}
pieces[3][3][4] = {0,0,3,0,0}
pieces[3][3][5] = {0,0,0,0,0}

pieces[3][4][1] = {0,0,0,0,0}
pieces[3][4][2] = {0,0,0,3,0}
pieces[3][4][3] = {0,3,3,3,0}
pieces[3][4][4] = {0,0,0,0,0}
pieces[3][4][5] = {0,0,0,0,0}

--L mirrored
pieces[4][1][1] = {0,0,0,0,0}
pieces[4][1][2] = {0,0,4,0,0}
pieces[4][1][3] = {0,0,4,0,0}
pieces[4][1][4] = {0,4,4,0,0}
pieces[4][1][5] = {0,0,0,0,0}

pieces[4][2][1] = {0,0,0,0,0}
pieces[4][2][2] = {0,4,0,0,0}
pieces[4][2][3] = {0,4,4,4,0}
pieces[4][2][4] = {0,0,0,0,0}
pieces[4][2][5] = {0,0,0,0,0}

pieces[4][3][1] = {0,0,0,0,0}
pieces[4][3][2] = {0,0,4,4,0}
pieces[4][3][3] = {0,0,4,0,0}
pieces[4][3][4] = {0,0,4,0,0}
pieces[4][3][5] = {0,0,0,0,0}

pieces[4][4][1] = {0,0,0,0,0}
pieces[4][4][2] = {0,4,4,4,0}
pieces[4][4][3] = {0,0,0,4,0}
pieces[4][4][4] = {0,0,0,0,0}
pieces[4][4][5] = {0,0,0,0,0}

--s 
pieces[5][1][1] = {0,0,0,0,0}
pieces[5][1][2] = {0,0,0,5,0}
pieces[5][1][3] = {0,0,5,5,0}
pieces[5][1][4] = {0,0,5,0,0}
pieces[5][1][5] = {0,0,0,0,0}

pieces[5][2][1] = {0,0,0,0,0}
pieces[5][2][2] = {0,0,0,0,0}
pieces[5][2][3] = {0,5,5,0,0}
pieces[5][2][4] = {0,0,5,5,0}
pieces[5][2][5] = {0,0,0,0,0}

pieces[5][3][1] = {0,0,0,0,0}
pieces[5][3][2] = {0,0,5,0,0}
pieces[5][3][3] = {0,5,5,0,0}
pieces[5][3][4] = {0,5,0,0,0}
pieces[5][3][5] = {0,0,0,0,0}

pieces[5][4][1] = {0,0,0,0,0}
pieces[5][4][2] = {0,5,5,0,0}
pieces[5][4][3] = {0,0,5,5,0}
pieces[5][4][4] = {0,0,0,0,0}
pieces[5][4][5] = {0,0,0,0,0}

--s mirrored
pieces[6][1][1] = {0,0,0,0,0}
pieces[6][1][2] = {0,0,6,0,0}
pieces[6][1][3] = {0,0,6,6,0}
pieces[6][1][4] = {0,0,0,6,0}
pieces[6][1][5] = {0,0,0,0,0}

pieces[6][2][1] = {0,0,0,0,0}
pieces[6][2][2] = {0,0,0,0,0}
pieces[6][2][3] = {0,0,6,6,0}
pieces[6][2][4] = {0,6,6,0,0}
pieces[6][2][5] = {0,0,0,0,0}

pieces[6][3][1] = {0,0,0,0,0}
pieces[6][3][2] = {0,6,0,0,0}
pieces[6][3][3] = {0,6,6,0,0}
pieces[6][3][4] = {0,0,6,0,0}
pieces[6][3][5] = {0,0,0,0,0}

pieces[6][4][1] = {0,0,0,0,0}
pieces[6][4][2] = {0,0,6,6,0}
pieces[6][4][3] = {0,6,6,0,0}
pieces[6][4][4] = {0,0,0,0,0}
pieces[6][4][5] = {0,0,0,0,0}

--T 
pieces[7][1][1] = {0,0,0,0,0}
pieces[7][1][2] = {0,0,7,0,0}
pieces[7][1][3] = {0,0,7,7,0}
pieces[7][1][4] = {0,0,7,0,0}
pieces[7][1][5] = {0,0,0,0,0}

pieces[7][2][1] = {0,0,0,0,0}
pieces[7][2][2] = {0,0,0,0,0}
pieces[7][2][3] = {0,7,7,7,0}
pieces[7][2][4] = {0,0,7,0,0}
pieces[7][2][5] = {0,0,0,0,0}

pieces[7][3][1] = {0,0,0,0,0}
pieces[7][3][2] = {0,0,7,0,0}
pieces[7][3][3] = {0,7,7,0,0}
pieces[7][3][4] = {0,0,7,0,0}
pieces[7][3][5] = {0,0,0,0,0}

pieces[7][4][1] = {0,0,0,0,0}
pieces[7][4][2] = {0,0,7,0,0}
pieces[7][4][3] = {0,7,7,7,0}
pieces[7][4][4] = {0,0,0,0,0}
pieces[7][4][5] = {0,0,0,0,0}





SE_screen_init(width,height,bpp)

--SE_audio_init(44100,16,1)

--SE_audio_enablesound()

SE_input_init()

joystick = SE_input_open(0)

state = SE_input_state_init()

--font = SE_image_load("font512.png")

images = SE_image_load("data/images.png")

quit = 0

x = 0
y = 0
z = 0

while (quit == 0) do

	SE_screen_clear(0.5,1,0.5,1)

	--SE_image_draw(images,x,y,z)

	state = SE_input_poll(joystick)

	if(SE_input_button(state,"JOY_UP") == 1) then
		y = y - 4
	end

	if(SE_input_button(state,"JOY_DOWN") == 1) then
		y = y + 4
	end

	if(SE_input_button(state,"JOY_LEFT") == 1) then
		x = x - 4
	end

	if(SE_input_button(state,"JOY_RIGHT") == 1) then
		x = x + 4
	end

	if(SE_input_button(state,"SE_QUIT") == 1) then
		quit = 1
	end
		
	SE_screen_flip()		

end

--SE_image_clean(font)
--SE_image_clean(char)
SE_input_close()




