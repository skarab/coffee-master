function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6416\" class=\"headerLeftMenuInActive\"><a id=\"aID6416\" href=\"#\" OnMouseOver=\"link('_dir','character0',this)\" class=\"leftMenuLinkHeadInActive\">character</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID937\" class=\"leftMenuInActive\"><a id=\"aID937\" href=\"#\" OnMouseOver=\"link('_class','CharacterController35940',this)\" class=\"leftMenuLinkInActive\">CharacterController</a></div>\n");
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
