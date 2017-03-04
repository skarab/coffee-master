function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6443\" class=\"headerLeftMenuInActive\"><a id=\"aID6443\" href=\"#\" OnMouseOver=\"link('_dir','button0',this)\" class=\"leftMenuLinkHeadInActive\">button</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1016\" class=\"leftMenuInActive\"><a id=\"aID1016\" href=\"#\" OnMouseOver=\"link('_class','Button45101',this)\" class=\"leftMenuLinkInActive\">Button</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6237\" class=\"leftMenuInActive\"><a id=\"aID6237\" href=\"#\" OnMouseOver=\"link('_member','BUTTON_STATE1141535755',this)\" class=\"leftMenuLinkInActive\">BUTTON_STATE</a></div>\n");
document.write("<div id=\"divID6238\" class=\"leftMenuInActive\"><a id=\"aID6238\" href=\"#\" OnMouseOver=\"link('_member','BUTTON_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">BUTTON_STYLE</a></div>\n");
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
