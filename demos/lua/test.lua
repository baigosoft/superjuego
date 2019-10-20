width = 640
height = 480
bpp = 32

SE_screen_init(width,height,bpp)

image = SE_image_load("prueba.png")

image01 = SE_image_load("run01.png")
image02 = SE_image_load("run02.png")

caja = SE_box_init(4,4,32,32)

SE_box_position_set(caja,8,8)
SE_box_dimentions_set(caja,128,8)

transf = SE_transf_init()

SE_transf_position_set(transf,20,20,200)

x,y,z= SE_transf_get(transf)

anim = SE_ani_init(128,128,2)

SE_ani_addframe(anim,image01,0,10)
SE_ani_addframe(anim,image02,1,10)

animator = SE_animator_init(anim)


print(x)
print(y)
print(z)


for i=1,500 do
	SE_screen_clear(0.5,1,0.5,1)
	SE_image_draw(image,0,0,0)
	SE_image_draw(image,200,200,0)
	SE_image_segment_draw(image,0,0,150,150,300,300,0)
	SE_animator_draw(animator,300,200,0)
	SE_screen_flip()		
end

SE_image_clean(image)
SE_animator_clean(animator)
SE_ani_clean(anim)
SE_image_clean(image01)
SE_image_clean(image02)


print("comanse esta putos")
