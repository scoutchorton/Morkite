-- https://www.educba.com/lua-sleep/
local clock = os.clock
function sleep(n)-- seconds
	local t0 = clock()
	while clock() - t0 <= n do end
end


local x = 0

while x < 10 do
	print('Hello world from Lua! #'..x)
	x = x + 1
	--sleep(10)
end

setWindowTitle('PROJECT MORKITE: NOW WITH LUA!!!')

sleep(2.5)

setWindowTitle('ROCK AND STONE, TO THE BONE!!!')