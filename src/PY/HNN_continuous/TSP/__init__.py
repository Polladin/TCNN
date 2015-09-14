
import math
import random

class TSP_HNN_cont:

    U = []
    V = []
    A = 100 #500 #500
    B = 100 #500 #500
    C = 90 #0.1 #200 #200
    D = 90 #100 #500
    N = 7
    dt = 0.005
    al = 50
    K = 0.7

    sim_steps = 0
    city_amount = 0
    dist_matrix = []

    def __init__(self, init_sim_steps, init_city_amout, dist):
        self.dist_matrix = dist
        self.sim_steps = init_sim_steps
        self.city_amount = init_city_amout
        self.U = [[0] * init_city_amout for i in range(init_city_amout)]
        self.V = [[0] * init_city_amout for i in range(init_city_amout)]

        for i in range(init_city_amout):
#             self.V[i][i] = 0.5 * (1 + math.tanh(self.al * self.U[i][i]))
            for j in range(init_city_amout):
                self.V[i][j] = 0
                self.U[i][j] = random.random()

            self.V[i][i] = 1


    def sum_for_city(self, city):
        s_city = 0

        for pos in range(self.city_amount):
            if pos != city:
                s_city += self.V[city][pos]

        return s_city


    def sum_for_pos(self, pos):
        s_pos = 0

        for city in range(self.city_amount):
            if city != pos:
                s_pos +=  self.V[city][pos]

        return s_pos

    def sum_all(self):
        s_all = 0

        for city in range(self.city_amount):
            for pos in range(self.city_amount):
                s_all += self.V[city][pos]

        return s_all

    def sum_dist(self, in_city, in_pos):
        s_dist = 0

        for city in range(self.city_amount):
            s_dist += self.dist_matrix[in_city][city] * (  self.V[city][(in_pos-1)%self.city_amount]
                                                         + self.V[city][(in_pos+1)%self.city_amount] )
        return s_dist



    def run_discr(self):
        tmp_u = [[0] * self.city_amount for i in range(self.city_amount)]
        tmp_v = [[0] * self.city_amount for i in range(self.city_amount)]

        for step in range(self.sim_steps):
            for city in range(self.city_amount):
                for pos in range(self.city_amount):

#                     print("run city:" + str(city) + ' pos:' + str(pos))
#                     for k in range(len(self.V)):
#                         print(self.V[k])
#                     print(self.U)
#                     print(  'sum_city:' + str(self.sum_for_city(city)) \
#                           + '  sum_pos:' + str(self.sum_for_pos(pos))  \
#                           + '  sum_dist:' + str(self.sum_dist(city, pos)))  \
#                           + '  sum_all:' + str(self.sum_all())
                    tmp_u[city][pos] = self.K * self.U[city][pos]                \
                                 - self.A * self.sum_for_city(city)         \
                                 - self.B * self.sum_for_pos(pos)           \
                                 + self.C * (self.N - self.sum_all())       \
                                 - self.D * self.sum_dist(city, pos)

                    tmp_v[city][pos] = 0.5 * (1 + math.tanh(self.al * self.U[city][pos]))

            self.U = tmp_u
            self.V = tmp_v

#Analog Hopfield
    def run_analog(self):
#         tmp_u = [[0] * self.city_amount for i in range(self.city_amount)]
#         tmp_v = [[0] * self.city_amount for i in range(self.city_amount)]

        for step in range(self.sim_steps):
#             for city in range(self.city_amount):
            city = random.randrange(self.city_amount)
            pos = random.randrange(self.city_amount)
#                 for pos in range(self.city_amount):
            print("run city:" + str(city) + ' pos:' + str(pos))
            for k in range(len(self.V)):
                print(self.V[k])
            print(self.U)
            print(  'sum_city:' + str(self.sum_for_city(city)) \
                  + '  sum_pos:' + str(self.sum_for_pos(pos))  \
                  + '  sum_dist:' + str(self.sum_dist(city, pos)))  \
                  + '  sum_all:' + str(self.sum_all())

            self.U[city][pos] = self.U[city][pos]                                                       \
                                            + self.dt * (- self.U[city][pos] - self.A * self.sum_for_city(city)      \
                                                 - self.B * self.sum_for_pos(pos)                               \
                                                 + self.C * (self.N - self.sum_all())                           \
                                                 - self.D * self.sum_dist(city, pos)                         )

            self.V[city][pos] = 0.5 * (1 + math.tanh(self.al * self.U[city][pos]))

#         self.U = tmp_u
#         self.V = tmp_v


CITY_IN_LINE = 3
CITY_AMOUNT = 6
dist = [[0] * CITY_AMOUNT for i in range(CITY_AMOUNT)]

for i in range(CITY_AMOUNT):
    for j in range(CITY_AMOUNT):
        dist[i][j] = math.sqrt(math.pow((j %  CITY_IN_LINE) - (i %  CITY_IN_LINE),2) + math.pow((j /  CITY_IN_LINE) - (i /  CITY_IN_LINE),2))
        dist[j][i] = math.sqrt(math.pow((j %  CITY_IN_LINE) - (i %  CITY_IN_LINE),2) + math.pow((j /  CITY_IN_LINE) - (i /  CITY_IN_LINE),2))

print('dist')
for k in range(len(dist)):
    print(dist[k])


cl = TSP_HNN_cont(1000, CITY_AMOUNT, dist)
# cl.run_analog()
cl.run_discr()

for i in range(len(cl.V)):
    for k in range(len(cl.V[i])):
        cl.V[i][k] = round(cl.V[i][k])

for k in range(len(cl.V)):
    print (cl.V[k])




