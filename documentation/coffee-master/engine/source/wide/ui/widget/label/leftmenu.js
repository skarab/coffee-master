function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6450\" class=\"headerLeftMenuInActive\"><a id=\"aID6450\" href=\"#\" OnMouseOver=\"link('_dir','label0',this)\" class=\"leftMenuLinkHeadInActive\">label</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1024\" class=\"leftMenuInActive\"><a id=\"aID1024\" href=\"#\" OnMouseOver=\"link('_class','Label45101',this)\" class=\"leftMenuLinkInActive\">Label</a></div>\n");
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
