SIZE = 9
KOMI = 6.5

EMPTY = 0
BLACK = 1
WHITE = 2

TONARI = None


def _load_tonari():
    global TONARI
    TONARI = [None] * (SIZE * SIZE)
    for i in xrange(SIZE):
        for j in xrange(SIZE):
            tonari = []
            if i != 0:
                tonari.append((i - 1) * SIZE + j)
            if j != 0:
                tonari.append(i * SIZE + (j - 1))
            if i != SIZE - 1:
                tonari.append((i + 1) * SIZE + j)
            if i != SIZE - 1:
                tonari.append(i * SIZE + (j + 1))
            TONARI[i * SIZE + j] = tonari
_load_tonari()


class Game(object):
    def __init__(self):
        self.board = [EMPTY] * (SIZE * SIZE)
        self.captures = [0, 0]

    def has_lib(self, loc):
        init_color = self.board[loc]
        if init_color == EMPTY:
            return True

        frontier = []
        inspected = set([loc])

        while True:
            for tonari in TONARI[loc]:
                color = self.board[tonari]
                if color == 0:
                    return True
                elif color == init_color:
                    if tonari not in inspected:
                        frontier.append(tonari)
            if not frontier:
                return False
            loc = frontier.pop()
            inspected.add(loc)

    def kill_group(self, loc):
        init_color = self.board[loc]
        if init_color == EMPTY:
            return 0

        frontier = []
        inspected = set([loc])
        killed = 0

        while True:
            self.board[loc] = EMPTY
            killed += 1
            for tonari in TONARI[loc]:
                color = self.board[tonari]
                if color == init_color:
                    if tonari not in inspected:
                        frontier.append(tonari)
            if not frontier:
                return killed
            loc = frontier.pop()
            inspected.add(loc)

    def play(self, pos, color):
        x, y = pos
        loc = x * SIZE + y
        if self.board[loc] != EMPTY:
            return False

        self.board[loc] = color

        killing = []
        for tonari in TONARI[loc]:
            if color == 3 - self.board[tonari] and not self.has_lib(tonari):
                killing.append(tonari)

        if not any(killing) and not self.has_lib(loc):
            self.board[loc] = EMPTY
            return False

        for tonari in killing:
            self.captures[color - 1] += self.kill_group(tonari)

        return True


    def __str__(self):
        s = ''
        for i in xrange(SIZE):
            for j in xrange(SIZE):
                color = self.board[i * SIZE + j]
                if color == 0:
                    if i in (2, 6) and j in (2, 6):
                        s += '+'
                    else:
                        s += '.'
                elif color == 1:
                    s += 'X'
                elif color == 2:
                    s += 'O'
                s += ' '
            s += '\n'
        s += "X:%d, O:%d+%s" % (self.captures[0], self.captures[1], KOMI)
        return s

def test():
    b = Game()
    b.play((0, 0), BLACK);
    b.play((0, 2), BLACK);

    b.play((1, 0), WHITE);
    b.play((1, 2), WHITE);
    b.play((0, 3), WHITE);
    b.play((0, 1), WHITE);

    b.play((1, 1), BLACK);
    b.play((2, 0), BLACK);
    b.play((0, 0), BLACK);
    b.play((1, 0), BLACK);

    b.play((2, 1), WHITE);
    b.play((3, 0), WHITE);

    #print b

if __name__ == '__main__':
    import time
    a = time.time()
    for i in xrange(1000000):
        test()
    b = time.time()
    print "TIME:", b - a
