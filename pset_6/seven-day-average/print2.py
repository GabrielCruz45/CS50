def main():

    my_dict = {}

    # my_dict['Puerto Rico'] = 1
    my_dict.setdefault('Puerto Rico', [])
    my_dict['Puerto Rico'].append(2)
    my_dict['Puerto Rico'].append(3)
    my_dict['Puerto Rico'].append(int('4'))
    my_dict['Puerto Rico'].append(5)
    # my_dict['Puerto Rico'].pop(0)
    print(my_dict['Puerto Rico'])
    x = len(my_dict['Puerto Rico'])
    if len(my_dict['Puerto Rico']) < 14:
        print('hola')

    print(x)

main()