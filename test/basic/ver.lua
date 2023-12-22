local i = 0
while true do
    local cur = vm.version[i]
    if cur == nil then
        break
    end
    print('bb' .. tostring(i) .. ' = ' .. tostring(cur))
    i = i + 1
end