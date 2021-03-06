#  **************************************************************************  #
'''
#   BornAgain: simulate and fit scattering at grazing incidence
#
#   @file      Wrap/python.plot_utils
#   @brief     Python extensions of the SWIG-generated Python module bornagain.
#
#   @homepage  http://apps.jcns.fz-juelich.de/BornAgain
#   @license   GNU General Public License v3 or higher (see COPYING)
#   @copyright Forschungszentrum Juelich GmbH 2016
#   @authors   Scientific Computing Group at MLZ Garching
#   @authors   J. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
'''
#  **************************************************************************  #
from __future__ import print_function
import bornagain as ba
from bornagain import deg as deg
from bornagain import IFitObserver as IFitObserver
try:  # workaround for build servers
    import numpy as np
    from matplotlib import pyplot as plt
    from matplotlib import gridspec, colors
except Exception as e:
    print("In plot_utils.py: {:s}".format(str(e)))


label_fontsize = 16


def get_axes_limits(result, units):
    """
    Returns axes range as expected by pyplot.imshow.
    :param result: SimulationResult object from a Simulation
    :param units: units to use
    :return: axes ranges as a flat list
    """
    axis_infos = result.axisInfo(units)
    limits = [ [axis_infos[i].m_min, axis_infos[i].m_max] for i in range(len(axis_infos)) ]
    flat_limits = [ v for sublist in limits for v in sublist ]

    return flat_limits


def translate_axis_label(label):
    """
    Formats an axis label into a LaTeX representation
    :param label: text representation of the axis label
    :return: LaTeX representation
    """
    label_dict = {
                 'X [nbins]'     : r'$X \; (bins)$',
                 'phi_f [rad]'   : r'$\varphi_f \; (rad)$',
                 'phi_f [deg]'   : r'$\varphi_f \; (deg)$',
                 'alpha_i [rad]' : r'$\alpha_i \; (rad)$',
                 'alpha_i [deg]' : r'$\alpha_i \; (deg)$',
                 'X [mm]'        : r'$X \; (mm)$',
                 'Qy [1/nm]'     : r'$Q_y \; (nm^{-1})$',
                 'Q [1/nm]'      : r'$Q \; (nm^{-1})$',

                 'Y [nbins]'     : r'$Y \; (bins)$',
                 'alpha_f [rad]' : r'$\alpha_f \; (rad)$',
                 'alpha_f [deg]' : r'$\alpha_f \; (deg)$',
                 'Y [mm]'        : r'$Y \; (mm)$',
                 'Qz [1/nm]'     : r'$Q_z \; (nm^{-1})$',
                 'Position [nm]' : r'$Position \; (nm)$'
                 }
    if label in label_dict.keys():
        return label_dict[label]
    else:
        return label


def get_axes_labels(result, units):
    """
    Returns axes range as expected by pyplot.imshow.
    :param result: SimulationResult object from a Simulation
    :param units: units to use
    :return: axes ranges as a flat list
    """
    axis_infos = result.axisInfo(units)
    labels = [ translate_axis_label(axis_infos[i].m_name) for i in range(len(axis_infos)) ]

    return labels


def plot_array(array, zmin=None, zmax=None, xlabel=None, ylabel=None, zlabel=None,
               title=None, axes_limits=None):
    """
    Plots numpy array as a colormap in log scale.
    """

    zlabel = "Intensity" if zlabel is None else zlabel

    zmax = np.amax(array) if zmax is None else zmax
    zmin = 1e-6*zmax if zmin is None else zmin

    if zmin == zmax == 0.0:
        norm = colors.Normalize(0, 1)
    else:
        norm = colors.LogNorm(zmin, zmax)

    im = plt.imshow(array, norm=norm, extent=axes_limits, aspect='auto')
    cb = plt.colorbar(im, pad=0.025)

    if xlabel:
        plt.xlabel(xlabel, fontsize=label_fontsize)

    if ylabel:
        plt.ylabel(ylabel, fontsize=label_fontsize)

    if zlabel:
        cb.set_label(zlabel, size=label_fontsize)

    if title:
        plt.title(title)


def plot_histogram(hist, zmin=None, zmax=None, xlabel=None, ylabel=None, zlabel=None,
                  title=None):
    """
    Plots intensity data as color map
    :param intensity: Histogram2D object obtained from GISASSimulation
    :param zmin: Min value on amplitude's color bar
    :param zmax: Max value on amplitude's color bar
    """

    if not xlabel:
        xlabel = translate_axis_label(hist.getXaxis().getName())

    if not ylabel:
        ylabel = translate_axis_label(hist.getYaxis().getName())

    axes_limits = [hist.getXmin(), hist.getXmax(),
                   hist.getYmin(), hist.getYmax()]

    plot_array(hist.array(), zmin=zmin, zmax=zmax, xlabel=xlabel, ylabel=ylabel,
               zlabel=zlabel, title=title, axes_limits=axes_limits)


def plot_colormap(result, zmin=None, zmax=None, units=ba.AxesUnits.DEFAULT,
                  xlabel=None, ylabel=None, zlabel=None,
                  title=None):
    """
    Plots intensity data as color map
    :param result: SimulationResult from GISAS/OffSpecSimulation
    :param zmin: Min value on amplitude's color bar
    :param zmax: Max value on amplitude's color bar
    """

    axes_limits = get_axes_limits(result, units)
    axes_labels = get_axes_labels(result, units)
    xlabel = axes_labels[0] if xlabel is None else xlabel
    ylabel = axes_labels[1] if ylabel is None else ylabel

    plot_array(result.array(), zmin=zmin, zmax=zmax, xlabel=xlabel, ylabel=ylabel,
               zlabel=zlabel, title=title, axes_limits=axes_limits)


def plot_specular_simulation_result(result, ymin=None, ymax=None, units=ba.AxesUnits.DEFAULT,
              xlabel=None, ylabel=None, title=None):
    """
    Plots intensity data for specular simulation result
    :param result: SimulationResult from SpecularSimulation
    :param ymin: minimal y-axis value to show
    :param ymax: maximum y-axis value to show
    :param units: units on the x-axis
    """

    data = result.data(units)
    intensity = data.getArray()
    x_axis = data.getAxis(0).getBinCenters()
    ymax = np.amax(intensity) * 2.0 if ymax is None else ymax
    ymin = max(np.amin(intensity) * 0.5, 1e-18 * ymax) if ymin is None else ymin

    xlabel = get_axes_labels(result, units)[0] if xlabel is None else xlabel
    ylabel = "Intensity" if ylabel is None else ylabel

    plt.semilogy(x_axis, intensity)

    plt.ylim([ymin, ymax])

    if xlabel:
        plt.xlabel(xlabel, fontsize=label_fontsize)

    if ylabel:
        plt.ylabel(ylabel, fontsize=label_fontsize)

    if title:
        plt.title(title)


def plot_simulation_result(result, intensity_min=None, intensity_max=None, units=ba.AxesUnits.DEFAULT,
                           postpone_show=False):
    """
    Draws simulation result and (optionally) shows the plot.
    :param result_: SimulationResult object obtained from GISAS/OffSpec/SpecularSimulation
    :param intensity_min: Min value on amplitude's axis or color bar
    :param intensity_max: Max value on amplitude's axis or color bar
    :param units: units for plot axes
    :param postpone_show: postpone showing the plot for later tuning (False by default)
    """
    if len(result.array().shape) == 1:  # 1D data, specular simulation assumed
        plot_specular_simulation_result(result, intensity_min, intensity_max)
    else:
        plot_colormap(result, intensity_min, intensity_max, units)
    plt.tight_layout()
    if not postpone_show:
        plt.show()


class Plotter:
    def __init__(self):

        self._fig = plt.figure(figsize=(10.25, 7.69))
        self._fig.canvas.draw()

    def reset(self):
        self._fig.clf()

    def plot(self, fit_suite):
        self._fig.tight_layout()
        plt.pause(0.03)


class PlotterGISAS(Plotter):
    def __init__(self):
        Plotter.__init__(self)

    @staticmethod
    def make_subplot(nplot):
        plt.subplot(2, 2, nplot)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)

    def plot(self, fit_suite):
        Plotter.reset(self)

        real_data = fit_suite.experimentalData()
        sim_data = fit_suite.simulationResult()
        diff = fit_suite.relativeDifference()

        self.make_subplot(1)

        # same limits for both plots
        arr = real_data.array()
        zmax = np.amax(arr)
        zmin = zmax*1e-6

        plot_colormap(real_data, title="\"Experimental\" data", zmin=zmin, zmax=zmax,
                      xlabel='', ylabel='', zlabel='')

        self.make_subplot(2)
        plot_colormap(sim_data, title="Simulated data", zmin=zmin, zmax=zmax,
                      xlabel='', ylabel='', zlabel='')

        self.make_subplot(3)
        plot_colormap(diff, title="Relative difference", zmin=0.001, zmax=10.0,
                       xlabel='', ylabel='', zlabel='')

        self.make_subplot(4)
        plt.title('Parameters')
        plt.axis('off')
        plt.text(0.01, 0.85, "Iterations  " + '{:d}     {:s}'.
                 format(fit_suite.numberOfIterations(), fit_suite.minimizer().minimizerName()))
        plt.text(0.01, 0.75, "Chi2       " + '{:8.4f}'.format(fit_suite.getChi2()))
        for index, fitPar in enumerate(fit_suite.fitParameters()):
            plt.text(0.01, 0.55 - index * 0.1, '{:30.30s}: {:6.3f}'.format(fitPar.name(), fitPar.value()))

        Plotter.plot(self, fit_suite)


class PlotterSpecular(Plotter):
    """
    Draws fit progress every nth iteration. This class has to be attached to
    FitSuite via attachObserver method. Intended specifically for observing
    specular data fit.
    FitSuite kernel will call DrawObserver's update() method every n'th iteration.
    """

    def __init__(self, draw_every_nth=10):
        Plotter.__init__(self)
        self.gs = gridspec.GridSpec(1, 2, width_ratios=[2.5, 1], wspace=0)

    @staticmethod
    def as_si(val, ndp):
        """
        Fancy print of scientific-formatted values
        :param val: numeric value
        :param ndp: number of decimal digits to print
        :return: a string corresponding to the _val_
        """
        s = '{x:0.{ndp:d}e}'.format(x=val, ndp=ndp)
        m, e = s.split('e')
        return r'{m:s}\times 10^{{{e:d}}}'.format(m=m, e=int(e))

    @staticmethod
    def trunc_str(token, length):
        """
        Truncates token if it is longer than length.

        Example:
            trunc_str("123456789", 8) returns "123456.."

            trunc_str("123456789", 9) returns "123456789"

        :param token: input string
        :param length: max non-truncated length
        :return:
        """
        return (token[:length - 2] + '..') if len(token) > length else token

    def plot_table(self, fit_suite):

        # definitions and values
        trunc_length = 9  # max string field width in the table
        n_digits = 1  # number of decimal digits to print
        n_iterations = fit_suite.numberOfIterations()  # number of iterations
        minimizer = fit_suite.minimizer().minimizerName()
        rel_dif = fit_suite.relativeDifference().array().max()  # maximum relative difference
        fitted_parameters = fit_suite.fitParameters()

        # creating table content
        labels = ("Parameter", "Value")
        table_data = [["Minimizer", '{:s}'.format(self.trunc_str(minimizer, trunc_length))],
                      ["Iteration", '${:d}$'.format(n_iterations)],
                      ["$d_{r, max}$", '${:s}$'.format(self.as_si(rel_dif, n_digits))]]
        for fitPar in fitted_parameters:
            table_data.append(['{:s}'.format(self.trunc_str(fitPar.name(), trunc_length)),
                               '${:s}$'.format(self.as_si(fitPar.value(), n_digits))])

        # creating table
        axs = plt.subplot(self.gs[1])
        axs.axis('tight')
        axs.axis('off')
        table = plt.table(cellText=table_data, colLabels=labels, cellLoc='center',
                          loc='bottom left', bbox=[0.0, 0.0, 1.0, 1.0])

        # # setting alignment to center in 0th column
        # for key, cell in table.get_celld().items():
        #     col = key[1]
        #     if col == 0:
        #         cell._loc = 'center'  # accessing private member is the only option to change alignment for one cell

    def plot_graph(self, fit_suite):
        # retrieving data from fit suite
        real_data = fit_suite.experimentalData().histogram1d()
        sim_data = fit_suite.simulationResult().histogram1d()

        # normalizing axis coordinates
        axis = sim_data.getXaxis().getBinCenters()
        axis_values = [value for value in axis]

        # default font properties dictionary to use
        font = {'family': 'serif',
                'weight': 'normal',
                'size': label_fontsize}

        plt.subplot(self.gs[0])
        plt.semilogy(axis_values, sim_data.array(), 'b',
                     axis_values, real_data.array(), 'k--')
        plt.ylim((0.5 * real_data.getMinimum(), 5 * real_data.getMaximum()))
        plt.legend(['BornAgain', 'Reference'], loc='upper right', prop=font)
        plt.xlabel(sim_data.getXaxis().getName(), fontdict=font)
        plt.ylabel("Intensity", fontdict=font)
        plt.title("Specular data fitting", fontdict=font)

    def plot(self, fit_suite):
        Plotter.reset(self)

        self.plot_graph(fit_suite)
        self.plot_table(fit_suite)

        Plotter.plot(self, fit_suite)


class DefaultFitObserver(IFitObserver):
    """
    Draws fit progress every nth iteration. This class has to be attached to
    FitSuite via attachObserver method.
    FitSuite kernel will call DrawObserver's update() method every n'th iteration.
    It is up to the user what to do here.
    """
    import sys
    import traceback

    def __init__(self, draw_every_nth=10, SimulationType='GISAS'):
        """
        Initializes observer
        :param draw_every_nth: specifies when to output data, defaults to each 10th iteration
        :param SimulationType: simulation type underlying fitting:
            'GISAS' - GISAS simulation, default

            'Specular' - specular simulation

        """
        IFitObserver.__init__(self, draw_every_nth)
        if SimulationType is 'GISAS':
            self._plotter = PlotterGISAS()
        elif SimulationType is 'Specular':
            self._plotter = PlotterSpecular()
        else:
            raise Exception("Unknown simulation type {:s}.".format(SimulationType))

    def update(self, fit_suite):
        self._plotter.plot(fit_suite)

