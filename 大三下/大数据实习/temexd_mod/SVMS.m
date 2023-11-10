function [trainedClassifier, validationAccuracy] = trainClassifier(trainingData)
% [trainedClassifier, validationAccuracy] = trainClassifier(trainingData)
% 返回经过训练的分类器及其 准确度。以下代码重新创建在 Classification Learner App 中训
% 练的分类模型。您可以使用该生成的代码基于新数据自动训练同一模型，或通过它了解如何以程序化方
% 式训练模型。
%
%  输入:
%      trainingData: 一个与导入 App 中的矩阵具有相同列数和数据类型的矩阵。
%
%  输出:
%      trainedClassifier: 一个包含训练的分类器的结构体。该结构体中具有各种关于所训练分
%       类器的信息的字段。
%
%      trainedClassifier.predictFcn: 一个对新数据进行预测的函数。
%
%      validationAccuracy: 一个包含准确度百分比的双精度值。在 App 中，"历史记录" 列
%       表显示每个模型的此总体准确度分数。
%
% 使用该代码基于新数据来训练模型。要重新训练分类器，请使用原始数据或新数据作为输入参数
% trainingData 从命令行调用该函数。
%
% 例如，要重新训练基于原始数据集 T 训练的分类器，请输入:
%   [trainedClassifier, validationAccuracy] = trainClassifier(T)
%
% 要使用返回的 "trainedClassifier" 对新数据 T2 进行预测，请使用
%   yfit = trainedClassifier.predictFcn(T2)
%
% T2 必须是仅包含用于训练的预测变量列的矩阵。有关详细信息，请输入:
%   trainedClassifier.HowToPredict

% 由 MATLAB 于 2022-07-01 00:55:34 自动生成


% 提取预测变量和响应
% 以下代码将数据处理为合适的形状以训练模型。
%
% 将输入转换为表
inputTable = array2table(trainingData, 'VariableNames', {'column_1', 'column_2', 'column_3', 'column_4', 'column_5', 'column_6', 'column_7', 'column_8', 'column_9', 'column_10', 'column_11', 'column_12', 'column_13', 'column_14', 'column_15', 'column_16', 'column_17', 'column_18', 'column_19', 'column_20', 'column_21', 'column_22', 'column_23', 'column_24', 'column_25', 'column_26', 'column_27', 'column_28', 'column_29', 'column_30', 'column_31', 'column_32', 'column_33', 'column_34', 'column_35', 'column_36', 'column_37', 'column_38', 'column_39', 'column_40', 'column_41', 'column_42'});

predictorNames = {'column_1', 'column_2', 'column_3', 'column_4', 'column_5', 'column_6', 'column_7', 'column_8', 'column_9', 'column_10', 'column_11', 'column_12', 'column_13', 'column_14', 'column_15', 'column_16', 'column_17', 'column_18', 'column_19', 'column_20', 'column_21', 'column_22', 'column_23', 'column_24', 'column_25', 'column_26', 'column_27', 'column_28', 'column_29', 'column_30', 'column_31', 'column_32', 'column_33', 'column_34', 'column_35', 'column_36', 'column_37', 'column_38', 'column_39', 'column_40', 'column_41'};
predictors = inputTable(:, predictorNames);
response = inputTable.column_42;
isCategoricalPredictor = [false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false];

% 训练分类器
% 以下代码指定所有分类器选项并训练分类器。
template = templateSVM(...
    'KernelFunction', 'gaussian', ...
    'PolynomialOrder', [], ...
    'KernelScale', 1.6, ...
    'BoxConstraint', 1, ...
    'Standardize', true);
classificationSVM = fitcecoc(...
    predictors, ...
    response, ...
    'Learners', template, ...
    'Coding', 'onevsone', ...
    'ClassNames', [1; 2; 3; 4]);

% 使用预测函数创建结果结构体
predictorExtractionFcn = @(x) array2table(x, 'VariableNames', predictorNames);
svmPredictFcn = @(x) predict(classificationSVM, x);
trainedClassifier.predictFcn = @(x) svmPredictFcn(predictorExtractionFcn(x));

% 向结果结构体中添加字段
trainedClassifier.ClassificationSVM = classificationSVM;
trainedClassifier.About = '此结构体是从 Classification Learner R2020b 导出的训练模型。';
trainedClassifier.HowToPredict = sprintf('要对新预测变量列矩阵 X 进行预测，请使用: \n yfit = c.predictFcn(X) \n将 ''c'' 替换为作为此结构体的变量的名称，例如 ''trainedModel''。\n \nX 必须包含正好 41 个列，因为此模型是使用 41 个预测变量进行训练的。\nX 必须仅包含与训练数据具有完全相同的顺序和格式的\n预测变量列。不要包含响应列或未导入 App 的任何列。\n \n有关详细信息，请参阅 <a href="matlab:helpview(fullfile(docroot, ''stats'', ''stats.map''), ''appclassification_exportmodeltoworkspace'')">How to predict using an exported model</a>。');

% 提取预测变量和响应
% 以下代码将数据处理为合适的形状以训练模型。
%
% 将输入转换为表
inputTable = array2table(trainingData, 'VariableNames', {'column_1', 'column_2', 'column_3', 'column_4', 'column_5', 'column_6', 'column_7', 'column_8', 'column_9', 'column_10', 'column_11', 'column_12', 'column_13', 'column_14', 'column_15', 'column_16', 'column_17', 'column_18', 'column_19', 'column_20', 'column_21', 'column_22', 'column_23', 'column_24', 'column_25', 'column_26', 'column_27', 'column_28', 'column_29', 'column_30', 'column_31', 'column_32', 'column_33', 'column_34', 'column_35', 'column_36', 'column_37', 'column_38', 'column_39', 'column_40', 'column_41', 'column_42'});

predictorNames = {'column_1', 'column_2', 'column_3', 'column_4', 'column_5', 'column_6', 'column_7', 'column_8', 'column_9', 'column_10', 'column_11', 'column_12', 'column_13', 'column_14', 'column_15', 'column_16', 'column_17', 'column_18', 'column_19', 'column_20', 'column_21', 'column_22', 'column_23', 'column_24', 'column_25', 'column_26', 'column_27', 'column_28', 'column_29', 'column_30', 'column_31', 'column_32', 'column_33', 'column_34', 'column_35', 'column_36', 'column_37', 'column_38', 'column_39', 'column_40', 'column_41'};
predictors = inputTable(:, predictorNames);
response = inputTable.column_42;
isCategoricalPredictor = [false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false];

% 执行交叉验证
partitionedModel = crossval(trainedClassifier.ClassificationSVM, 'KFold', 5);

% 计算验证预测
[validationPredictions, validationScores] = kfoldPredict(partitionedModel);

% 计算验证准确度
validationAccuracy = 1 - kfoldLoss(partitionedModel, 'LossFun', 'ClassifError');
