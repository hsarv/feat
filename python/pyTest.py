from feat import Feat
import numpy
from sklearn.datasets import load_boston

boston = load_boston()
X = boston.data


Y = boston.target
print('initial constructor...')
clf= Feat(verbosity=1)

print('calling fit..')
clf.fit(X,Y)

print('representation: ', clf.get_representation())

print (clf.predict(X))
print (clf.transform(X))
print (clf.fit_predict(X,Y))
print (clf.fit_transform(X,Y))
