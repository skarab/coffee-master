function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6459\" class=\"headerLeftMenuInActive\"><a id=\"aID6459\" href=\"#\" OnMouseOver=\"link('_dir','tree_control0',this)\" class=\"leftMenuLinkHeadInActive\">tree_control</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1034\" class=\"leftMenuInActive\"><a id=\"aID1034\" href=\"#\" OnMouseOver=\"link('_class','TreeControl45101',this)\" class=\"leftMenuLinkInActive\">TreeControl</a></div>\n");
document.write("<div id=\"divID1035\" class=\"leftMenuInActive\"><a id=\"aID1035\" href=\"#\" OnMouseOver=\"link('_class','TreeControlItem45101',this)\" class=\"leftMenuLinkInActive\">TreeControlItem</a></div>\n");
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
