#!/bin/bash
#
# run_all_trigSFs.sh
# 
# 1) Step1: 트리거 효율 계산 (SF 미적용)
# 2) Step2: TriggerEfficiency macro 실행 → ScaleFactors.root 생성
# 3) Step3: SF 적용 후 트리거 효율 계산
# 4) Step4: PlotTriggerEfficiency macro 실행 → 최종 플롯 생성
#

set -e  # Any error → abort

#-------------------------------------------------------------------------------
# Configuration
#-------------------------------------------------------------------------------
# Data and MC sample names (without .root)
DATA_SAMPLES=(SingleMuon_B SingleMuon_C SingleMuon_D SingleMuon_E SingleMuon_F)
MC_SAMPLES=(ttJets)

# Debug flag for exe_TrigStudy: 1=verbose, 0=quiet
DEBUG=0

# Output directories
STEP1_DIR="TriggerStep01_NoSF"
STEP2_DIR="TriggerStep02_WithSF"

#-------------------------------------------------------------------------------
# Step 1: Compute efficiencies without SF
#-------------------------------------------------------------------------------
echo "[Step1] Computing trigger efficiencies (no SF)..."
for s in "${MC_SAMPLES[@]}" "${DATA_SAMPLES[@]}"; do
    echo "  -> Sample: $s"
    ./exe_TrigStudy "$s" 0 ${DEBUG} &
done
wait
echo "[Step1] Done."

#-------------------------------------------------------------------------------
# Organize Step1 outputs
#-------------------------------------------------------------------------------
echo "[Step1] Organizing outputs into ./${STEP1_DIR}"
rm -rf "${STEP1_DIR}"
mkdir -p "${STEP1_DIR}"
mv output_*.root "${STEP1_DIR}/"
cp TriggerEfficiency.cpp "${STEP1_DIR}/"
cp PlotTriggerEfficiency.cpp "${STEP1_DIR}/"  # in case macro needs plotting functions
echo "[Step1] Files moved."

#-------------------------------------------------------------------------------
# Step 2: Derive Scale Factors
#-------------------------------------------------------------------------------
echo "[Step2] Deriving scale factors with TriggerEfficiency macro..."
pushd "${STEP1_DIR}" > /dev/null

# Merge all data histograms into single Data.root (needed by macro)
echo "  -> Merging Data histos"
hadd -f Data.root SingleMuon_*.root

# Run the macro (assumes it reads Data.root and ttJets.root in this directory)
root -l -b -q "TriggerEfficiency.cpp"

popd > /dev/null
echo "[Step2] ScaleFactors.root generated in ${STEP1_DIR}."

#-------------------------------------------------------------------------------
# Step 3: Compute efficiencies with SF applied
#-------------------------------------------------------------------------------
echo "[Step3] Computing trigger efficiencies (with SF)..."
for s in "${MC_SAMPLES[@]}" "${DATA_SAMPLES[@]}"; do
    echo "  -> Sample: $s"
    ./exe_TrigStudy "$s" 1 ${DEBUG} &
done
wait
echo "[Step3] Done."

#-------------------------------------------------------------------------------
# Organize Step3 outputs
#-------------------------------------------------------------------------------
echo "[Step3] Organizing outputs into ./${STEP2_DIR}"
rm -rf "${STEP2_DIR}"
mkdir -p "${STEP2_DIR}"
mv corrected_*.root "${STEP2_DIR}/"
cp PlotTriggerEfficiency.cpp "${STEP2_DIR}/"
echo "[Step3] Files moved."

#-------------------------------------------------------------------------------
# Step 4: Plot corrected efficiencies
#-------------------------------------------------------------------------------
echo "[Step4] Plotting corrected trigger efficiencies..."
pushd "${STEP2_DIR}" > /dev/null

# Merge corrected data histos
echo "  -> Merging corrected Data histos"
hadd -f corrected_Data.root corrected_SingleMuon_*.root

# For convenience, rename corrected_ttJets → ttJets
cp corrected_ttJets.root ttJets.root

# Run the plotting macro
root -l -b -q "PlotTriggerEfficiency.cpp"

popd > /dev/null
echo "[Step4] Plots generated in ${STEP2_DIR}."

echo "=== All steps completed successfully ==="
