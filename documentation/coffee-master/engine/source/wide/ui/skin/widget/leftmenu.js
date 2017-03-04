function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6441\" class=\"headerLeftMenuInActive\"><a id=\"aID6441\" href=\"#\" OnMouseOver=\"link('_dir','widget0',this)\" class=\"leftMenuLinkHeadInActive\">widget</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1001\" class=\"leftMenuInActive\"><a id=\"aID1001\" href=\"#\" OnMouseOver=\"link('_class','SkinButton49249',this)\" class=\"leftMenuLinkInActive\">SkinButton</a></div>\n");
document.write("<div id=\"divID1002\" class=\"leftMenuInActive\"><a id=\"aID1002\" href=\"#\" OnMouseOver=\"link('_class','SkinCheckBox49249',this)\" class=\"leftMenuLinkInActive\">SkinCheckBox</a></div>\n");
document.write("<div id=\"divID1003\" class=\"leftMenuInActive\"><a id=\"aID1003\" href=\"#\" OnMouseOver=\"link('_class','SkinDialog49249',this)\" class=\"leftMenuLinkInActive\">SkinDialog</a></div>\n");
document.write("<div id=\"divID1004\" class=\"leftMenuInActive\"><a id=\"aID1004\" href=\"#\" OnMouseOver=\"link('_class','SkinEditBox49249',this)\" class=\"leftMenuLinkInActive\">SkinEditBox</a></div>\n");
document.write("<div id=\"divID1005\" class=\"leftMenuInActive\"><a id=\"aID1005\" href=\"#\" OnMouseOver=\"link('_class','SkinGroup49249',this)\" class=\"leftMenuLinkInActive\">SkinGroup</a></div>\n");
document.write("<div id=\"divID1006\" class=\"leftMenuInActive\"><a id=\"aID1006\" href=\"#\" OnMouseOver=\"link('_class','SkinImage49249',this)\" class=\"leftMenuLinkInActive\">SkinImage</a></div>\n");
document.write("<div id=\"divID1007\" class=\"leftMenuInActive\"><a id=\"aID1007\" href=\"#\" OnMouseOver=\"link('_class','SkinLabel49249',this)\" class=\"leftMenuLinkInActive\">SkinLabel</a></div>\n");
document.write("<div id=\"divID1008\" class=\"leftMenuInActive\"><a id=\"aID1008\" href=\"#\" OnMouseOver=\"link('_class','SkinMenuItem49249',this)\" class=\"leftMenuLinkInActive\">SkinMenuItem</a></div>\n");
document.write("<div id=\"divID1009\" class=\"leftMenuInActive\"><a id=\"aID1009\" href=\"#\" OnMouseOver=\"link('_class','SkinProgressBar49249',this)\" class=\"leftMenuLinkInActive\">SkinProgressBar</a></div>\n");
document.write("<div id=\"divID1010\" class=\"leftMenuInActive\"><a id=\"aID1010\" href=\"#\" OnMouseOver=\"link('_class','SkinScrollBar49249',this)\" class=\"leftMenuLinkInActive\">SkinScrollBar</a></div>\n");
document.write("<div id=\"divID1011\" class=\"leftMenuInActive\"><a id=\"aID1011\" href=\"#\" OnMouseOver=\"link('_class','SkinToolTip49249',this)\" class=\"leftMenuLinkInActive\">SkinToolTip</a></div>\n");
document.write("<div id=\"divID1012\" class=\"leftMenuInActive\"><a id=\"aID1012\" href=\"#\" OnMouseOver=\"link('_class','SkinTreeControlItem49249',this)\" class=\"leftMenuLinkInActive\">SkinTreeControlItem</a></div>\n");
document.write("<div id=\"divID1013\" class=\"leftMenuInActive\"><a id=\"aID1013\" href=\"#\" OnMouseOver=\"link('_class','SkinViewContainer49249',this)\" class=\"leftMenuLinkInActive\">SkinViewContainer</a></div>\n");
document.write("<div id=\"divID1014\" class=\"leftMenuInActive\"><a id=\"aID1014\" href=\"#\" OnMouseOver=\"link('_class','SkinViewControl49249',this)\" class=\"leftMenuLinkInActive\">SkinViewControl</a></div>\n");
document.write("<div id=\"divID1015\" class=\"leftMenuInActive\"><a id=\"aID1015\" href=\"#\" OnMouseOver=\"link('_class','SkinWindow49249',this)\" class=\"leftMenuLinkInActive\">SkinWindow</a></div>\n");
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
