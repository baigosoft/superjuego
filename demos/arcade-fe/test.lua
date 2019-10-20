width = 640
height = 480
bpp = 32

SE_screen_init(width,height,bpp)

SE_audio_init(44100,16,1)

SE_audio_enablesound()



SE_input_init()

joystick = SE_input_open(0)

state = SE_input_state_init()

font = SE_image_load("font512.png")

char = SE_image_load("char.png")

sound = SE_audio_loadsound("sonido.wav")

music = SE_audio_loadmusic("musica.ogg")

SE_audio_enablemusic()

quit = 0

x = 100
y = 100
z = 0

SE_audio_playmusic(music)

while (quit == 0) do

	SE_screen_clear(0.5,1,0.5,1)

	SE_image_draw(char,x,y,z)

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

SE_image_clean(font)
SE_image_clean(char)
SE_input_close()




