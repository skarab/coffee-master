function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6445\" class=\"headerLeftMenuInActive\"><a id=\"aID6445\" href=\"#\" OnMouseOver=\"link('_dir','combo_box0',this)\" class=\"leftMenuLinkHeadInActive\">combo_box</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1018\" class=\"leftMenuInActive\"><a id=\"aID1018\" href=\"#\" OnMouseOver=\"link('_class','ComboBox45101',this)\" class=\"leftMenuLinkInActive\">ComboBox</a></div>\n");
document.write("<div id=\"divID1019\" class=\"leftMenuInActive\"><a id=\"aID1019\" href=\"#\" OnMouseOver=\"link('_class','ComboBoxProperty45101',this)\" class=\"leftMenuLinkInActive\">ComboBoxProperty</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
