function [fitresult, gof] = poly(test_x, test_y)
%CREATEFIT(TEST_X,TEST_Y)
%  Create a fit.
%
%  Data for 'poly' fit:
%      X Input : test_x
%      Y Output: test_y
%  Output:
%      fitresult : a fit object representing the fit.
%      gof : structure with goodness-of fit info.
%
%  另请参阅 FIT, CFIT, SFIT.

%  由 MATLAB 于 19-May-2022 15:36:58 自动生成


%% Fit: 'poly'.
[xData, yData] = prepareCurveData( test_x, test_y );

% Set up fittype and options.
ft = fittype( 'poly1' );

% Fit model to data.
[fitresult, gof] = fit( xData, yData, ft );

% Plot fit with data.
figure( 'Name', 'poly' );
h = plot( fitresult, xData, yData );
legend( h, 'test_y vs. test_x', 'poly', 'Location', 'NorthEast', 'Interpreter', 'none' );
% Label axes
xlabel( 'test_x', 'Interpreter', 'none' );
ylabel( 'test_y', 'Interpreter', 'none' );
grid on


